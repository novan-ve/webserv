/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 18:01:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "includes/Request.hpp"
#include "ReadUtils.hpp"

Request::Request() {}

Request::Request(const std::string& requestMethod, const std::string &file_path) : method(requestMethod), path(file_path) {}

Request::Request(const Request& other) : method(other.method), path(other.path) {}

Request& Request::operator = (const Request& other)
{
	if (this != &other)
	{
		this->method = other.method;
		this->path = other.path;
	}
	return (*this);
}

Request::~Request() {}

void Request::saveRequest(std::vector<std::string> &lines) {

	std::vector<std::string>::iterator	header_end;

	// Get position of empty line between header and body
	for (header_end = lines.begin(); header_end != lines.end(); header_end++) {
		if (*header_end == "\r")
			break;
	}

	// Place header values inside headers attribute
	for (std::vector<std::string>::iterator it = lines.begin(); it != header_end; it++) {
		if ((*it).find(':') != std::string::npos) {
			std::pair<std::string, std::string>	keyval = ft::get_keyval(*it);
			this->headers.push_back(keyval);
		}
	}

	// If a body exists, place lines inside body attribute
	if (header_end != lines.end() && ++header_end != lines.end()) {
		for (std::vector<std::string>::iterator it = header_end; it != lines.end(); it++)
			this->body.push_back(*it);
	}
}

void	Request::printRequest(void) const {
	// Print values for debugging
	std::cout << std::endl << "Request:" << std::endl;
	std::cout << "  Headers:" << std::endl;
	std::cout << "\t" << this->method << " " << this->path << " HTTP/1.1" << std::endl;
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++) {
		std::cout << "\t" << it->first << ": " << it->second << std::endl;
	}
	if (this->body.size()) {
		std::cout << "  Body:" << std::endl;
		for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
			std::cout << "\t" << *it << std::endl;
	}
	else {
		std::cout << "  No body" << std::endl;
	}
}

std::string		Request::get_method() const { return this->method; }
std::string		Request::get_path() const { return this->path; }
