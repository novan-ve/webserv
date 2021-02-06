/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 23:28:03 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/04 23:28:06 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <sys/socket.h>

#include "includes/Response.hpp"
#include "includes/Utilities.hpp"

Response::Response(Request *request, int code=200) : req(request), response_code(code) {

	this->setStatusCodes();
}

Response::Response(int code) : response_code(code) {

	this->setStatusCodes();

	this->status_line.append("HTTP/1.1 " + this->status_codes[code]);
	this->headers.push_back(std::make_pair<std::string, std::string>("Server", "webserv/1.0"));
	this->headers.push_back(std::make_pair<std::string, std::string>("Date", ft::getTime()));
	this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/html"));
	this->setBodyError();
	this->headers.push_back(std::make_pair<std::string, std::string>("Content-Length", this->getBodyLength()));
	this->headers.push_back(std::make_pair<std::string, std::string>("Connection", "close"));
}

Response::~Response() {}

Response::Response(const Response& other) : req(other.req), status_line(other.status_line), response_code(other.response_code) {

	this->setStatusCodes();
}

Response& Response::operator = (const Response& other)
{
	if (this != &other)
	{
		this->req = other.req;
	}
	return (*this);
}

void		Response::setStatusCodes(void) {

	this->status_codes[200] = "200 OK";
	this->status_codes[400] = "400 Bad Request";
	this->status_codes[404] = "404 Not Found";
	this->status_codes[505] = "505 HTTP Version Not Supported";
}

std::string Response::getBodyLength(void) const {

	std::stringstream	ss;
	std::string			result;
	int 				total = 0;

	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
		total += (*it).size();

	ss << total;
	ss >> result;

	return result;
}

void	Response::setBodyError(void) {

	this->body.push_back("<html>\n");
	this->body.push_back("<head><title>" + this->status_codes[this->response_code] + "</title></head>\n");
	this->body.push_back("<body>\n");
	this->body.push_back("<center><h1>" + this->status_codes[this->response_code] + "</h1></center>\n");
	this->body.push_back("<hr><center>webserv/1.0</center>\n");
	this->body.push_back("</body>\n");
	this->body.push_back("</html>\n");
}

void	Response::composeResponse(void) {

	this->status_line.append("HTTP/1.1 ");

	if (this->req->get_faulty_header())
		this->response_code = 400;

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
		this->body.push_back("Spoderman\n");
		this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/plain"));
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
