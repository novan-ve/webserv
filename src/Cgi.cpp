/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cgi.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:59:06 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/03/22 17:44:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "Cgi.hpp"
#include "Utilities.hpp"
#include <exception>

Cgi::Cgi() {
	ft::memset(this->args, (int)NULL, sizeof(args));
}

Cgi::Cgi(const Cgi & src)
{
	*this = src;
}

Cgi &	Cgi::operator=(const Cgi & rhs)
{
	if (this != &rhs)
	{
		this->_vars = rhs._vars;
		this->_env = rhs._env;
	}

	return *this;
}

Cgi::~Cgi() {

	int		i = 0;

	for (size_t i = 0; i < 3; i++)
		free(args[i]);

	while (this->_env[i])
	{
		free(this->_env[i]);
		this->_env[i] = 0;
		i++;
	}
	if (this->_env)
	{
		free(this->_env);
		this->_env = 0;
	}
	this->_vars.clear();
}

void	Cgi::set_env(Request *req, std::string path, std::string host, std::string port, std::string phpcgi)
{
	this->_vars["AUTH_TYPE"] = req->get_header("Authorization");
	if (req->get_header("Content-Length") == "")
	{
		if (req->get_header("Transfer-Encoding") == "")
			this->_vars["CONTENT_LENGTH"] = "0";
		else
		{
			int	len = 0;
			for (std::vector<std::string>::iterator it = req->get_body().begin(); it != req->get_body().end(); it++)
				len += (*it).size();
			this->_vars["CONTENT_LENGTH"] = ft::itos(len);
		}
	}
	else
		this->_vars["CONTENT_LENGTH"] = req->get_header("Content-Length");
	this->_vars["CONTENT_TYPE"] = req->get_header("Content-Type");
	this->_vars["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_vars["PATH_INFO"] = req->uri.get_uri();

	char buf[512];
	std::string	root = getcwd(buf, 512);
	this->_vars["PATH_TRANSLATED"] = root + req->uri.get_uri();
	if ( req->get_path().length() > 3 && req->get_path().substr(req->get_path().length() - 4, 4) == ".php" && !phpcgi.empty())
	{
		this->_vars["QUERY_STRING"] = req->uri.get_query();
		for (std::vector<std::string>::iterator it = req->get_body().begin(); it != req->get_body().end(); it++)
			this->_vars["QUERY_STRING"] += *it;
	}
	else
		this->_vars["QUERY_STRING"] = "";
	this->_vars["REMOTE_ADDR"] = "localhost";
	this->_vars["REMOTE_IDENT"] = "";
	this->_vars["REMOTE_USER"] = "";
	this->_vars["REQUEST_METHOD"] = req->get_method();
	this->_vars["REQUEST_URI"] = req->uri.get_uri();
	this->_vars["SCRIPT_NAME"] = path;
	this->_vars["SCRIPT_FILENAME"] = path;
	this->_vars["SERVER_NAME"] = host;
	this->_vars["SERVER_PORT"] = port;
	this->_vars["SERVER_PROTOCOL"] = "HTTP/1.1";
	this->_vars["SERVER_SOFTWARE"] = "HTTP/1.1";
	this->_vars["REDIRECT_STATUS"] = "true";

	for (std::map<std::string, std::string>::iterator it = req->get_headers().begin(); it != req->get_headers().end(); it++)
		this->_vars["HTTP_" + ft::toUpperStr(it->first)] = it->second;

	int 	i = 0;
	this->_env = (char**)malloc(sizeof(char *) * (this->_vars.size() + 1));

	for (std::map<std::string, std::string>::iterator it = this->_vars.begin(); it != this->_vars.end(); it++)
	{
		this->_env[i] = ft::strdup((it->first + "=" + it->second).c_str());
		if (!this->_env[i])
		{
			for (int j = i - 1; j >= 0; j--)
				free(this->_env[j]);
			free(this->_env);
			throw std::runtime_error("Error: malloc failed in Cgi::set_this->_env");
		}
		i++;
	}
	this->_env[i] = 0;
}

void	Cgi::execute(Request *req, std::string path, std::string host, std::string port, std::string phpcgi)
{
	pid_t	pid;
	int 	in_fd, out_fd, status;

	this->args[0] = ft::strdup(&path[0]);
	if ((req->get_method() == "POST" || req->get_path().substr(req->get_path().length() - 4, 4) == ".php") &&
		!phpcgi.empty())
	{
		free(this->args[0]);
		this->args[0] = ft::strdup((phpcgi).c_str());
		if (!this->args[0])
			throw std::runtime_error("Error: malloc failed in Cgi::execute");
		this->args[1] = ft::strdup(path.c_str());
		if (!this->args[1])
			throw std::runtime_error("Error: malloc failed in Cgi::execute");
	}

	this->args[2] = NULL;
	this->set_env(req, path, host, port, phpcgi);

	if ((in_fd = open("/tmp/webservin", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		throw std::runtime_error("Error: open failed in Cgi::execute");

	for (std::vector<std::string>::iterator it = req->get_body().begin(); it != req->get_body().end(); it++)
	{
		if ((write(in_fd, (*it).c_str(), (*it).length())) == -1)
		{
			close(in_fd);
			throw std::runtime_error("Error: failed writing to previously opened /tmp/webservin");
		}
	}
	if (close(in_fd) == -1)
		throw std::runtime_error("Error: close failed in Cgi::execute");

	pid = fork();
	if (pid == -1)
	{
		std::cout << "Fork failed with error code: " << strerror(NULL) << std::endl;
		throw std::runtime_error("Error: fork failed in Cgi::execute");
	}

	if (pid == 0)
	{
		if ((out_fd = open("/tmp/webservout", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
			throw std::runtime_error("Error: open failed in Cgi::execute");
		if (dup2(out_fd, STDOUT_FILENO) == -1 || close(out_fd) == -1)
			throw std::runtime_error("Error: dup2/close failed in Cgi::execute");
		if ((in_fd = open("/tmp/webservin", O_RDONLY)) == -1)
			throw std::runtime_error("Error: open failed in Cgi::execute");
		if (dup2(in_fd, STDIN_FILENO) == -1 || close(in_fd) == -1)
			throw std::runtime_error("Error: dup2/close failed in Cgi::execute");
		if ((execve(this->args[0], this->args, this->_env)) == -1)
			throw std::runtime_error("Error: execve failed in Cgi::execute");
		throw std::runtime_error("Error: something went wrong in Cgi::execute");
	}
	waitpid(0, &status, 0);
}
