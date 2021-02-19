/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cgi.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 13:59:06 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/17 13:59:08 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include "Cgi.hpp"
#include "Utilities.hpp"
#include "Exception.hpp"

Cgi::Cgi() {}

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

void	Cgi::set_env(Request *req, std::string path, std::string host, std::string port)
{
	this->_vars["AUTH_TYPE"] = req->get_header("Authorization");
	this->_vars["CONTENT_LENGTH"] = req->getBodyLen();
	this->_vars["CONTENT_TYPE"] = req->get_header("Content_type");
	this->_vars["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->_vars["PATH_INFO"] = req->uri.get_uri();

	char buf[512];
	std::string	root = getcwd(buf, 512);
	this->_vars["PATH_TRANSLATED"] = root + req->uri.get_uri();
	this->_vars["QUERY_STRING"] = req->uri.get_query();
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
			throw ft::runtime_error("Error: malloc failed in Cgi::set_this->_env");
		}
		i++;
	}
	this->_env[i] = 0;
}

void	Cgi::execute(Request *req, std::string path, std::string host, std::string port)
{
	char	*args[3] = {&path[0], NULL, NULL};
	pid_t	pid;
	int 	ends[2];
	int 	in_fd;
	int 	status;

	// Change to php-cgi path from config
	if (req->get_path().length() > 4 && req->get_path().substr(req->get_path().length() - 4, 4) == ".php")
	{
		args[0] = ft::strdup("/usr/bin/php-cgi");
		if (!args[0])
			throw ft::runtime_error("Error: malloc failed in Cgi::execute");
		args[1] = ft::strdup(path.c_str());
		if (!args[1])
			throw ft::runtime_error("Error: malloc failed in Cgi::execute");
	}

	std::cout << "Args[0]: " << args[0] << std::endl;
	if (args[1] != NULL)
		std::cout << "Args[1]: " << args[1] << std::endl;

	args[2] = NULL;
	this->set_env(req, path, host, port);

	if ((in_fd = open("/tmp/webserv", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
		throw ft::runtime_error("Error: open failed in Cgi::execute");

	pipe(ends);

	if ((pid = fork()) == -1)
		throw ft::runtime_error("Error: fork failed in Cgi::execute");

	if (pid == 0)
	{
		if ((close(ends[1])) == -1)
			throw ft::runtime_error("Error: close failed in Cgi::execute");
		if ((dup2(ends[0], 0)) == -1)
			throw ft::runtime_error("Error: dup2 failed in Cgi::execute");
		if ((dup2(in_fd, 1)) == -1)
			throw ft::runtime_error("Error: open failed in Cgi::execute");
		if ((execve(args[0], args, this->_env)) == -1)
			throw ft::runtime_error("Error: execve failed in Cgi::execute");
		throw ft::runtime_error("Error: something went wrong in Cgi::execute");
	}
	else
	{
		if ((close(ends[0])) == -1)
			throw ft::runtime_error("Error: close failed in Cgi::execute");
	}

	waitpid(0, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);

	if (req->get_path().length() > 4 && req->get_path().substr(req->get_path().length() - 4, 4) == ".php")
	{
		free(args[0]);
		free(args[1]);
	}
	close(in_fd);
}

