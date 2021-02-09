/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 23:28:03 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/08 16:11:18 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include "includes/Response.hpp"
#include "includes/Utilities.hpp"

Response::Response(Request *request, int code) : req(request), response_code(code) {

	this->status_codes[200] = "200 OK";
	this->status_codes[400] = "400 Bad Request";
	this->status_codes[404] = "404 Not Found";
	this->status_codes[505] = "505 HTTP Version Not Supported";
}

Response::Response(const Response& other) : req(other.req), status_line(other.status_line),
											response_code(other.response_code) {}

Response& Response::operator = (const Response& other)
{
	if (this != &other)
	{
		this->req = other.req;
		this->status_line = other.status_line;
		this->response_code = other.response_code;
	}
	return (*this);
}

Response::~Response() {}

std::string Response::getBodyLength(void) const {

	std::string			result = "";
	int 				total = 0;

	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		total += (*it).size();

	while (total != 0) {
		result.insert(result.begin(), static_cast<char>(total % 10 + '0'));
		total /= 10;
	}

	return result;
}

void	Response::setBodyError(void) {

	this->body.push_back("<html>\n");
	this->body.push_back("<head><title>" + this->status_codes[this->response_code] + "</title></head>\n");
	this->body.push_back("<body>\n");
	this->body.push_back("<center><h1>" + this->status_codes[this->response_code] + "</h1></center>\n");
	this->body.push_back("<center><hr>webserv/1.0</center>\n");
	this->body.push_back("</body>\n");
	this->body.push_back("</html>\n");
}

void	Response::setContentType(std::string path) {

	if (path == "/")
		path = "/index.html";
	
	size_t		pos = path.find_last_of('.');

	if (pos == std::string::npos) {
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/plain"));
		return;
	}

	std::string	ext = path.substr(pos + 1, path.length() - pos - 1);
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

void	Response::readPath(void) {

	std::string		path = this->req->get_path();

	if (path == "/")
		path = "/index.html";

	path.insert(0, "./html");

	int fd = open(path.c_str(), O_RDONLY);
	if (fd == -1) {
		this->response_code = 404;
		return;
	}

	this->body = ft::get_lines(fd);
	close(fd);

	for (std::vector<std::string>::iterator it = this->body.begin(); it != body.end(); it++)
		(*it).append("\n");
}

void	Response::composeResponse(void) {

	if (this->response_code == 200)
		this->readPath();

	this->status_line.append("HTTP/1.1 ");
	this->status_line.append(this->status_codes[this->response_code]);

	this->headers.push_back(std::make_pair<std::string, std::string>("Server", "webserv/1.0"));
	this->headers.push_back(std::make_pair<std::string, std::string>("Date", ft::getTime()));

	if (this->response_code != 200) {

		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/html"));
		this->setBodyError();
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Length", this->getBodyLength()));
		this->headers.push_back(std::make_pair<std::string, std::string>("Connection", "close"));

	}
	else {
		this->setContentType(this->req->get_path());
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Length", this->getBodyLength()));
		this->headers.push_back(std::make_pair<std::string, std::string>("Connection", "keep-alive"));
	}
}

void	Response::sendResponse(int fd) const
{
	std::string response;

	// Copy status line into response
	response.append(this->status_line + "\n");

	// Copy headers into response
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++)
		response.append((*it).first + ": " + (*it).second + "\n");

	// Copy newline into response to seperate headers and body
	response.append("\n");

	// Copy body into response
	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		response.append(*it);

	if (send(fd, response.c_str(), response.length(), 0) < 0)
		throw std::runtime_error("Error: Could not send request to the client");
}

void	Response::printResponse(void) const {

	// Print values for debugging
	std::cout << std::endl << "Response:" << std::endl;
	std::cout << "  Headers:" << std::endl;
	std::cout << "\t" << this->status_line << std::endl;
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++) {
		std::cout << "\t" << it->first << ": " << it->second << std::endl;
	}
	std::cout << "  Body:" << std::endl;
	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		std::cout << "\t" << *it;
	std::cout << std::endl;
}
