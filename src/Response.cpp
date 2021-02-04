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

Response::Response(Request *request) : req(request) {}

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

void	Response::sendResponse(int fd) const
{
	std::string response;

//	// Copy headers into message
//	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++)
//		response.append(*it.first + ": " + *it.second);
//
//	// Copy newline into message
//	response.append('\n');
//
//	// Copy body into message
//	for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
//		response.append(*it);

	response.append("HTTP/1.1 200 OK\n");
	response.append("Content-Type: text/plain\n");
	response.append("Connection: keep-alive\n");
	response.append("\nSpoderman");

	if (send(fd, response.c_str(), response.length(), 0) < 0)
		throw std::runtime_error("Error: Could not send request to the client");
	return ;
}
