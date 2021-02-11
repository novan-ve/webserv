/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/11 14:04:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "includes/Request.hpp"
#include "includes/Exception.hpp"
#include "Utilities.hpp"

Request::Request() : done(false), status_line("") {}

Request::Request(const Request& other) {

	*this = other;
}

Request& Request::operator = (const Request& other)
{
	if (this != &other)
	{
		this->done = other.done;
		this->status_line = other.status_line;
		this->lines = other.lines;
	}
	return (*this);
}

Request::~Request() {}

//true if line is status_line, false otherwise
bool Request::isStatusLine(const std::string &line)
{
	if (!line.size())
		return (false);
	std::vector<std::string>	parts = ft::split(line, " \r", "\r");
	if (parts.size() != 4)
		return (false);
	if (parts[0].find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
		return (false);
	if (parts[2].substr(0, 5) != "HTTP/")
		return (false);
	size_t slash_pos = parts[2].find('/');
	std::vector<std::string>	version = ft::split(parts[2].substr(slash_pos + 1, parts[2].size()), ".");
	if (version.size() != 2)
		return (false);
	if (version[0].find_first_not_of("0123456789") != std::string::npos)
		return (false);
	if (version[1].find_first_not_of("0123456789") != std::string::npos)
		return (false);
	if (parts[3] != "\r")
		return (false);
	return (true);
}

void Request::parseLine(std::string line) {

	if (line == "\r") {
		if (this->status_line == "")
			return;
		else if (this->status_line != "" && this->lines.size() == 0)
			throw(ft::reqException("invalid status_line", 400));
		else if (this->status_line != "" && this->lines.size() > 0) {

			int	end_pos_method = this->status_line.find(' ');
			int start_pos_path = end_pos_method;

			while (this->status_line[start_pos_path] == ' ')
				start_pos_path++;

			// Set end_pos_path to character before the \r\0 and remove whitespaces
			int end_pos_path = this->status_line.length() - 2;
			while (this->status_line[end_pos_path] == ' ')
				end_pos_path--;
			// Move back to first character before HTTP/1.1
			end_pos_path -= 8;

			// Remove white spaces and up 1 to get character right after path
			while (this->status_line[end_pos_path] == ' ')
				end_pos_path--;
			end_pos_path++;

			this->method = this->status_line.substr(0, end_pos_method);
			this->path = this->status_line.substr(start_pos_path, end_pos_path - start_pos_path);
			this->done = true;

			this->splitRequest();
			this->printRequest();

			return;
		}
	}
	else if (isStatusLine(line)) {
		if (this->status_line == "") {

			int start = line.length() - 1;

			while (line[start] == ' ' || (line[start] >= 10 && line[start] <= 13))
				start--;

			int end = start;

			while (line[start] != ' ')
				start--;

			if (line.substr(start + 1, end - start) != "HTTP/1.1")
				throw(ft::reqException("Error: unsupported Protocol/ProtocolVersion", 505));
			this->status_line = line;
		}
		return;
	}
	else if (line.find(':') != std::string::npos) {
		if (this->status_line == "")
			throw(ft::reqException("Error: Key Value pair found while expecting Status Line", 400));

		this->lines.push_back(line);
		return;
	}
	if (this->status_line != "")
		return;
	throw(ft::reqException("Error: Otherwise ill-formatted request encountered", 400));
}

void Request::splitRequest(void) {

	std::vector<std::string>::iterator	header_end;

	// Get position of empty line between header and body
	for (header_end = this->lines.begin(); header_end != this->lines.end(); header_end++) {
		if (*header_end == "\r")
			break;
	}

	// Place header values inside headers attribute
	for (std::vector<std::string>::iterator it = this->lines.begin(); it != header_end; it++) {
		if ((*it).find(':') != std::string::npos) {
			std::pair<std::string, std::string>	keyval = ft::get_keyval(*it);
			this->headers.push_back(keyval);
		}
	}

	// If a body exists, place this->lines inside body attribute
	if (header_end != this->lines.end() && ++header_end != this->lines.end()) {
		for (std::vector<std::string>::iterator it = header_end; it != this->lines.end(); it++)
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

bool			Request::get_done() const { return this->done; }
std::string		Request::get_method() const { return this->method; }
std::string		Request::get_path() const { return this->path; }
