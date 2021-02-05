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
#include <vector>
#include <sys/socket.h>

#include "includes/Response.hpp"
#include "includes/Utilities.hpp"

Response::Response(Request *request) : req(request), code(200) {}

Response::~Response() {}

Response::Response(const Response& other) : req(other.req) {}

Response& Response::operator = (const Response& other)
{
	if (this != &other)
	{
		this->req = other.req;
	}
	return (*this);
}

void	Response::composeResponse(void) {

	this->status_line.append("HTTP/1.1 ");

	if (this->req->get_faulty_header()) {

		this->code = 400;
		this->status_line.append("400 Bad Request");
	}
	else
		status_line.append("200 OK");

	this->headers.push_back(std::make_pair<std::string, std::string>("Server", "webserv/1.0"));
	this->headers.push_back(std::make_pair<std::string, std::string>("Date", ft::getTime()));
	this->headers.push_back(std::make_pair<std::string, std::string>("Content-Type", "text/plain"));

	if (this->code == 200)
		this->headers.push_back(std::make_pair<std::string, std::string>("Connection", "keep-alive"));
	else
		this->headers.push_back(std::make_pair<std::string, std::string>("Connection", "close"));

	this->body.push_back("Spoderman\n");
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
	return ;
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
		std::cout << "\t" << *it << std::endl;
}
