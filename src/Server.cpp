/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 16:21:50 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/04 15:12:29 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <fcntl.h>
#include <stdexcept>
#include <vector>

#include "includes/Server.hpp"
#include "includes/ReadUtils.hpp"
#include "includes/Utilities.hpp"
#include "includes/Response.hpp"

Server::Server() : _status_line("")
{
	int 	opt = 1;

	// Create socket file descriptor
	if ((this->_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw std::runtime_error("Error: Creation of socket failed");

	// Forcefully attach socket to port
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw std::runtime_error("Error: Failed to set socket options");

	// Assign transport address
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = ft::htons(PORT);
	ft::memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));

	// Attach socket to transport address
	if (bind(this->_server_fd, reinterpret_cast<struct sockaddr*>(&this->_address), sizeof( this->_address )) == -1)
		throw std::runtime_error("Error: binding server-socket to a port failed");

	//Set the resulting socketfd to be non blocking
	if (fcntl(this->_server_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error: Could not set server-socket to O_NONBLOCK");

	if (listen(this->_server_fd, 10 ) == -1)
		throw std::runtime_error("Error: could not set server-socket to listening mode");
	std::cout << "SERVER CREATED!" << std::endl;
}

Server::Server(const Server &src)
{
	*this = src;
}

Server&		Server::operator=(const Server &rhs)
{
	if (this != &rhs) {

		this->_server_fd = rhs._server_fd;

		this->_address.sin_family = rhs._address.sin_family;
		this->_address.sin_addr.s_addr = rhs._address.sin_addr.s_addr;
		this->_address.sin_port = rhs._address.sin_port;
		ft::memset(this->_address.sin_zero, '\0', sizeof(rhs._address.sin_zero));
	}

	return *this;
}

Server::~Server()
{
	std::cout << "DECONSTRUCTING SERVER" << std::endl;
	close(this->_server_fd);
}

int Server::errorResponse(int status_code, int new_socket) {

	Response	resp(status_code);

	resp.printResponse();
	resp.sendResponse(new_socket);

	this->_status_line = "";
	this->_lines.clear();

	return 2;
}

int Server::isStatusLine(const std::string &line) {

	size_t 		i = 0;

	// Search method
	while(i < line.length()) {

		// Method is at least 1 letter
		if (line[i] == ' ' && i > 0)
			break;

			// First word is smaller than 3 letters or bigger than 7 letters
		else if (line[i] == ' ' && (i < 2 || i > 7))
			return 0;

		// Not an uppercase letter
		if (line[i] < 'A' || line[i] > 'Z')
			return 0;
		i++;
	}
	// No spaces found
	if (line[i] == '\0')
		return 0;

	// Find start of path
	while (line[i] != '\0') {
		if (line[i] == '/')
			break;
		// Not a valid path
		if (line[i] != ' ')
			return 0;
		i++;
	}

	// No path found
	if (line[i] == '\0')
		return 0;

	// Find end of path
	while (line[i] != '\0') {
		if (line[i] == 'H')
			break;
			// Invalid character in path
		else if (line[i] < 20 || line[i] >= 127)
			return 0;
		i++;
	}

	// No HTTP version found or no space between path and http version
	if (line[i] == '\0' || line[i - 1] != ' ')
		return 0;

	// Version doesn't start with HTTP/
	if (line.substr(i, 5) != "HTTP/")
		return 0;
	i += 5;

	bool	dot = false;

	while (line[i] != '\0' && line[i] != '\r') {
		// Not a valid version number
		if (line[i] == ' ')
			break;
		if ((line[i] < '0' || line[i] > '9') && line[i] != '.')
			return 0;
		else if (line[i] == '.') {
			// Can't have more than 2 dots or have the dot not surrounded by numbers
			if (dot || line[i - 1] < '0' || line[i - 1] > '9' || line[i + 1] < '0' || line[i + 1] > '9')
				return 0;
			dot = true;
		}
		i++;
	}
	// No dot found
	if (!dot)
		return 0;

	while (line[i] == ' ')
		i++;

	// Has something after the HTTP version
	if (line[i] != '\0' && line[i] != '\r')
		return 0;

	return 1;
}

int Server::parseRequest(const std::string &line, int new_socket) {

	if (line == "\r") {
		if (this->_status_line == "")
			return 0;
		else if (this->_status_line != "" && this->_lines.size() == 0)
			return this->errorResponse(400, new_socket);
		else if (this->_status_line != "" && this->_lines.size() > 0) {

			int	end_pos_method = this->_status_line.find(' ');
			while (line[end_pos_method] == ' ')
				end_pos_method++;

			int end_pos_path = this->_status_line.substr(end_pos_method + 1, this->_status_line.length()).find(' ');

			Request	req(this->_status_line.substr(0, end_pos_method),
			   			this->_status_line.substr(end_pos_method + 1, end_pos_path - end_pos_method + 1));

			req.composeRequest(this->_lines);
			req.printRequest();
			this->handleResponse(new_socket, &req);
			return 1;
		}
	}
	else if (isStatusLine(line)) {
		if (this->_status_line == "") {

			int start = line.length() - 1;

			while (line[start] == ' ' || (line[start] >= 10 && line[start] <= 13))
				start--;

			int end = start;

			while (line[start] != ' ')
				start--;

			if (line.substr(start + 1, end - start) != "HTTP/1.1")
				return this->errorResponse(505, new_socket);
			this->_status_line = line;
		}
		return 0;
	}
	else if (line.find(':') != std::string::npos) {
		if (this->_status_line == "")
			return this->errorResponse(400, new_socket);

		this->_lines.push_back(line);
		return 0;
	}
	if (this->_status_line != "")
		return 0;
	return this->errorResponse(400, new_socket);
}

int	Server::handleRequest(int new_socket) {

	std::vector<std::string>	lines_read;

	lines_read = ft::get_lines(new_socket);

	// Telnet request
	if (lines_read.size() == 1) {
		if (parseRequest(lines_read[0], new_socket) == 2)
			return 1;
		return 0;
	}

	// Browser request
	for (std::vector<std::string>::iterator it = lines_read.begin(); it != lines_read.end(); it++) {
		if (parseRequest(*it, new_socket))
			return 1;
	}
	std::cout << "This isn't supposed to be printed, an error occurred in Server::handleRequest" << std::endl;
	return 1;
}

void	Server::handleResponse(int new_socket, Request *req) {

	Response	resp(req, 200);

	resp.composeResponse();
	resp.printResponse();
	resp.sendResponse(new_socket);

	this->_status_line = "";
	this->_lines.clear();
}
