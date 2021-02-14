/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 23:28:03 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/12 01:01:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include "includes/Response.hpp"
#include "includes/Utilities.hpp"

Response::Response()
{
	this->status_codes[200] = "200 OK";
	this->status_codes[400] = "400 Bad Request";
	this->status_codes[404] = "404 Not Found";
	this->status_codes[505] = "505 HTTP Version Not Supported";
}

Response::Response(const Response& other) : status_codes(other.status_codes), status_line(other.status_line),
											response_code(other.response_code) {}

void	Response::setRequest(Request& req)
{
	this->req = req;
	this->response_code = req.get_status_code();
}

int		Response::get_status_code() const
{
	return (this->response_code);
}

Response& Response::operator = (const Response& other)
{
	if (this != &other)
	{
		this->req = other.req;
		this->status_line = other.status_line;
		this->response_code = other.response_code;
		this->status_codes = other.status_codes;
	}
	return (*this);
}

Response::~Response() {}

void	Response::sendResponse(int fd) const
{
	std::string response;

	// Copy status line into response
	response.append(this->status_line + "\r\n");

	// Copy headers into response
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++)
		response.append((*it).first + ": " + (*it).second + "\r\n");

	// Copy newline into response to seperate headers and body
	response.append("\r\n");

	// Copy body into response
	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		response.append(*it + "\r\n");

	//response.append("\r\n");

	if (send(fd, response.c_str(), response.length(), 0) < 0)
		throw ft::runtime_error("Error: Could not send request to the client");
}

void	Response::printResponse(void) const
{
	// Print values for debugging
	std::cout << std::endl << "Response:" << std::endl;
	std::cout << "  Headers:" << std::endl;
	std::cout << "\t" << this->status_line << "\r" << std::endl;
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++) {
		std::cout << "\t" << it->first << ": " << it->second << "\r" << std::endl;
	}
	std::cout << "  Body:" << std::endl;
	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		std::cout << "\t" << *it << "\r" << std::endl;
	std::cout << std::endl;
}

void	Response::composeResponse(void)
{
	this->checkPath();

	this->setStatusLine();
	this->setServer();
	this->setDate();
	this->setContentType();
	this->setBody();
	this->setContentLen();
	this->setModified();
}

void	Response::checkPath(void)
{
	if (this->response_code != 200)
		return;
	this->path = this->req.get_path();

	if (this->path == "/")
		this->path = "/index.html";

	this->path.insert(0, "./html");

	int fd = open(this->path.c_str(), O_RDONLY);
	if (fd == -1) {
		this->response_code = 404;
		close(fd);
		return;
	}
	close(fd);
}

void	Response::setStatusLine(void)
{
	std::cout << "RESPONSE CODE: " << this->response_code << std::endl;
	this->status_line.append("HTTP/1.1 ");
	this->status_line.append(this->status_codes[this->response_code]);
}

void	Response::setServer(void)
{
	this->headers.push_back(std::make_pair<std::string, std::string>("Server", "webserv/1.0"));
}

void	Response::setDate(void)
{
	struct tm 	tm = ft::getTime();
	char		buf[64];

	ft::memset(buf, '\0', 64);
	strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm);

	this->headers.push_back(std::make_pair<std::string, std::string>("Date", std::string(buf)));
}

void	Response::setContentType()
{
	if (this->response_code != 200) {
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/html"));
		return;
	}

	size_t		pos = this->path.find_last_of('.');

	struct stat s;
	if (stat(path.c_str(), &s) != 0)
		throw ft::runtime_error("Stat failed in Response::setContentType()");

	if ( s.st_mode & S_IFDIR )
	{
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/html"));
		return;
	}

	if (pos == std::string::npos) {
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/plain"));
		return;
	}

	std::string	ext = this->path.substr(pos + 1, path.length() - pos - 1);
	std::string type;

	if (ext == "html" || ext == "css" || ext == "csv" || ext == "xml")
		type = "text/" + ext;
	else if (ext == "pdf" || ext == "json" || ext == "zip")
		type = "application/" + ext;
	else if (ext == "js")
		type = "application/javascript";
	else if (ext == "jpg" || ext == "jpeg")
		type = "image/jpeg";
	else if (ext == "gif" || ext == "png" || ext == "tiff")
		type = "image/" + ext;
	else if (ext == "ico")
		type = "image/x-icon";
	else if (ext == "mpeg" || ext == "mp4" || ext == "webm")
		type = "video/" + ext;
	else if (ext == "qt")
		type = "video/quicktime";
	else
		type = "application/octet-stream";

	this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", type));
}

void	Response::setBody(void)
{
	if (this->response_code != 200) {
		this->setBodyError();
		return;
	}
	struct stat s;
	if (stat(path.c_str(), &s) == 0) {

		if ( s.st_mode & S_IFDIR )
			this->listDirectory();
		else if ( s.st_mode & S_IFREG ) {

			std::cout << "BODY PATH: " << this->path << std::endl;
			int fd = open(this->path.c_str(), O_RDONLY);
			if (fd == -1)
				ft::runtime_error("Error: Response can't open previously checked file in setBody()");

			this->body = ft::get_lines(fd);
			close(fd);
		}
	}
}

void	Response::setBodyError(void)
{
	this->body.push_back("<html>");
	this->body.push_back("<head><title>" + this->status_codes[this->response_code] + "</title></head>");
	this->body.push_back("<body>");
	this->body.push_back("<center><h1>" + this->status_codes[this->response_code] + "</h1></center>");
	this->body.push_back("<center><hr>webserv/1.0</center>");
	this->body.push_back("</body>");
	this->body.push_back("</html>");
}

void	Response::listDirectory(void)
{
	struct stat 				result;
	struct dirent				*entry;
	char						buf[64];
	std::vector<std::string>	filenames;
	std::vector<std::string>	dirs;
	std::vector<std::string>	files;
	std::string					full_path = this->req.get_path();

	if (full_path[full_path.length() - 1] == '/')
		full_path.resize(full_path.find_last_not_of('/') + 1);

	this->body.push_back("<html>");
	this->body.push_back("<head><title>Index of " + full_path + "</title></head>");
	this->body.push_back("<body>");
	this->body.push_back("<h1>Index of " + full_path + "</h1><hr><pre><a href=\"..\">../</a>");

	DIR *dir = opendir(this->path.c_str());
	if (dir == NULL)
		throw ft::runtime_error("Error: opendir in Response::listDirectory failed");

	if (this->path[this->path.length() - 1] != '/')
		this->path.append("/");

	while ((entry = readdir(dir)) != NULL)
		filenames.insert(filenames.begin(), std::string(entry->d_name));
	closedir(dir);
	for (std::vector<std::string>::iterator it = filenames.begin(); it != filenames.end(); it++)
	{
		if (*it == "." || *it == "..")
			continue;
		if (stat((this->path + *it).c_str(), &result) == 0)
		{
			struct tm 	tm = ft::getTime(result.st_mtim.tv_sec);

			ft::memset(buf, '\0', 64);
			strftime(buf, sizeof(buf), "%d-%b-%Y %H:%M", &tm);

			if ( result.st_mode & S_IFDIR )
			{
				dirs.push_back("<a href=\"" + this->req.get_path());
				if (this->req.get_path()[this->req.get_path().length() - 1] != '/')
					dirs.back().append("/");
				dirs.back().append(*it + "/\">" + *it + "/</a>");
				dirs.back().append(std::string(50 - (*it).length(), ' ') + std::string(buf));
				dirs.back().append(std::string(19, ' ') + "-");
			}
			else if ( result.st_mode & S_IFREG )
			{
				files.push_back("<a href=\"" + this->req.get_path());
				if (this->req.get_path()[this->req.get_path().length() - 1] != '/')
					files.back().append("/");
				files.back().append(*it + "\">" + *it + "</a>");
				files.back().append(std::string(51 - (*it).length(), ' ') + std::string(buf));
				files.back().append(std::string(20 - ft::itos(result.st_size).length(), ' '));
				files.back().append(ft::itos(result.st_size));
			}
		}
	}
	for (std::vector<std::string>::iterator it = dirs.begin(); it != dirs.end(); it++)
		this->body.push_back(*it);
	for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++)
		this->body.push_back(*it);

	this->body.push_back("</pre><hr></body>");
	this->body.push_back("</html>");
}

void	Response::setContentLen(void)
{
	std::string			length = "";
	int 				total = 0;

	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		total += (*it).size() + 2;

	while (total != 0) {
		length.insert(length.begin(), static_cast<char>(total % 10 + '0'));
		total /= 10;
	}

	this->headers.push_back(std::make_pair<std::string, std::string>("Content-Length", length));
}

void	Response::setModified(void)
{
	if (this->response_code != 200)
		return;

	struct stat	result;

	if (stat(path.c_str(), &result) == 0)
	{
		if ( result.st_mode & S_IFREG )
		{
			struct tm 	tm = ft::getTime(result.st_mtim.tv_sec);
			char		buf[64];

			ft::memset(buf, '\0', 64);
			strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm);
			this->headers.push_back(std::make_pair<std::string, std::string>("Last-Modified", std::string(buf)));
		}
	}
}
