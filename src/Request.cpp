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

Request::Request(std::vector<std::string> &lines) : has_body(false), faulty_header(false) {

	std::vector<std::string>::iterator	header_end;

	// Get position of empty line between header and body
	for (header_end = lines.begin(); header_end != lines.end(); header_end++) {
		if (*header_end == "\r")
			break;
	}

	// Place header values inside headers attribute
	for (std::vector<std::string>::iterator it = lines.begin(); it != header_end; it++) {
		if (it == lines.begin()) {
			// Enables faulty_header and returns if request only contains 1 line
			if (it + 1 == header_end) {
				this->faulty_header = true;
				return;
			}
			this->status_line = *it;
		}
		else if ((*it).find(':') != std::string::npos) {
			std::pair<std::string, std::string>	keyval = ft::get_keyval(*it);
			this->headers.push_back(keyval);
		}
		// Return if line in header doesn't contain ':' and isn't the first line
		else {
			this->faulty_header = true;
			return;
		}
	}
	// If a body exists, place lines inside body attribute
	if (header_end != lines.end() && ++header_end != lines.end()) {
		this->has_body = true;
		for (std::vector<std::string>::iterator it = header_end; it != lines.end(); it++)
			this->body.push_back(*it);
	}
}

Request::~Request() {}

//Request::Request(const Request& other) : method(other.method) {}

Request& Request::operator = (const Request& other)
{
	if (this != &other)
	{
//		this->method = other.method;
	}
	return (*this);
}

void	Request::printRequest(void) const {
	// Print values for debugging
	std::cout << std::endl << "Request:" << std::endl;
	if (this->faulty_header) {
		std::cout << "  Faulty header" << std::endl;
		return;
	}
	std::cout << "  Headers:" << std::endl;
	std::cout << "\t" << this->status_line << std::endl;
	for (std::vector<std::pair<std::string, std::string> >::const_iterator it = this->headers.begin(); it != this->headers.end(); it++) {
		std::cout << "\t" << it->first << ": " << it->second << std::endl;
	}
	if (this->has_body) {
		std::cout << "  Body:" << std::endl;
		for (std::vector<std::string>::const_iterator it = this->body.begin(); it != this->body.end(); it++)
			std::cout << "\t" << *it << std::endl;
	}
	else {
		std::cout << "  No body" << std::endl;
	}
}

bool			Request::get_has_body() const { return this->has_body; }
bool			Request::get_faulty_header() const { return this->faulty_header; }
std::string		Request::get_status_line() const { return this->status_line; }
