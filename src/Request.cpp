/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/15 16:43:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "includes/Request.hpp"
#include "includes/Exception.hpp"
#include "Utilities.hpp"

Request::Request() : done(false), status_line(""), status_code(200) {}

Request::Request(const Request& other)
{
	*this = other;
}

Request& Request::operator = (const Request& other)
{
	if (this != &other)
	{
		this->done = other.done;
		this->status_line = other.status_line;
		this->lines = other.lines;
		this->status_code = other.status_code;
		this->path = other.path;
	}
	return (*this);
}

void	Request::process(int fd)
{
	std::vector <std::string> lines_read = ft::get_lines(fd);

	for (std::vector<std::string>::iterator it = lines_read.begin(); it != lines_read.end() && !this->done; it++)
	{
		std::cout << "REQUEST: " << *it << std::endl;
		this->done = parseLine(*it);
	}
}

Request::~Request() {}

//true if line is status_line, false otherwise
bool Request::isStatusLine(const std::string &line)
{
	size_t i = 0;
	if (!line.size() || line.size() >= 8000)
		return (false);
	std::vector<std::string>	parts = ft::split(line, " \r", " \r");
	//First part has to be METHOD
	if (parts[i++].find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
		return (false);
//	std::cout << "METHOD IS ONLY CAPS\n";
	//Has to have atleast one space
	if (parts[i++] != " ")
		return (false);
//	std::cout << "SEPARATED BY SPACE\n";
	//Skip over all spaces
	for (; parts[i] == " "; i++) {}
	//request-target has to start with '/'
	// if (parts[i][0] != '/')
	// 	return (false);
	//Request-line has to end on carriage return
	size_t end = parts.size() - 1;
	if (parts[end--] != "\r")
		return (false);
//	std::cout << "ENDS ON CARRIAGE RETURN\n";
	//Skip over all spaces that are at the end of the request-line
	for (;end > 0 && parts[end] == " "; end--) {}
	//Check if the version consists of HTTP/[0-9][0-9]
	if (parts[end].substr(0, 5) != "HTTP/")
		return (false);
//	std::cout << "PROTOCOL IS 'HTTP/'\n";
	std::vector<std::string>	version = ft::split(parts[end].substr(5, parts[end].size()), ".");
	if (version.size() != 2)
		return (false);
//	std::cout << "VERSION SIZE OF 2 ([0-9]\\.[0-9])\n";
	if (version[0].find_first_not_of("0123456789") != std::string::npos)
		return (false);
	if (version[1].find_first_not_of("0123456789") != std::string::npos)
		return (false);
//	std::cout << "VERSION IS ONLY NUMBERS\n";

	//Protocol has to have a minimum of one space before it
	if (parts[--end] != " ")
		return (false);
//	std::cout << "PROTOCOL SEPARATED FROM REQUEST-TARGET BY SPACE\n";
	if (i >= end)
		return (false);
	//Skip over all spaces preceding Protocol
	for (;end > i && parts[end] == " "; end--) {}

	//concatenate every part of the request-target together
	std::string request_target;
	for (--end; i < end; i++)
		request_target += parts[i];
	
	return (true);
}

bool	Request::parseLine(std::string line)
{
	if (line == "\r")
	{
		if (this->status_line == "")
			return false;
		else if (this->status_line != "" && this->lines.size() == 0)
		{
			this->status_code = 400;
			return (true);
		}
		else if (this->status_line != "" && this->lines.size() > 0)
		{
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

			this->splitRequest();
			this->printRequest();

			return (true);
		}
	}
	else if (isStatusLine(line))
	{
		if (this->status_line == "")
		{
			int start = line.length() - 1;

			while (line[start] == ' ' || (line[start] >= 10 && line[start] <= 13))
				start--;

			int end = start;

			while (line[start] != ' ')
				start--;

			if (line.substr(start + 1, end - start) != "HTTP/1.1")
			{
				this->status_code = 505;
				return (true);
			}
			this->status_line = line;
		}
		return (false);
	}
	else if (line.find(':') != std::string::npos)
	{
		if (this->status_line == "")
		{
			this->status_code = 400;
			return (true);
		}
		this->lines.push_back(line);
		return (false);
	}
	if (this->status_line != "")
		return (false);
	this->status_code = 400;
	return (true);
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
			std::pair<std::string, std::string>	keyval = ft::get_keyval(*it, ": ");
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
int				Request::get_status_code() const { return this->status_code; }
