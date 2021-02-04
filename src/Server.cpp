/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 16:21:50 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/04 02:15:20 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <fcntl.h>
#include <stdexcept>

#include "includes/Server.hpp"
#include "Utilities.hpp"

Server::Server()
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

//		dup2(this->_server_fd, rhs._server_fd); //dont think this is the right course of action for assignment
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

// void	Server::startListening( void )
// {
// 	unsigned int		addrlen = sizeof(this->_address);
// 	int 				new_socket;

// 	while(true) {

// 		std::cout << std::endl << "+++++++ Waiting for new connection ++++++++" << std::endl << std::endl;

// 		if ((new_socket = accept(this->_server_fd, reinterpret_cast<struct sockaddr*>(&this->_address),
// 				reinterpret_cast<socklen_t*>(&addrlen))) < 0)
// 			throw std::runtime_error("Error: error occurred when accepting a new client connection");

// 		this->parseRequest(new_socket);
// 		this->parseResponse(new_socket);

// 		std::cout << "------------------Hello message sent-------------------" << std::endl;

// 		close(new_socket);
// 	}
// }

void	Server::parseRequest(int new_socket) {

	char			buffer[1024];

	ft::memset(&buffer, '\0', 1024);

	if (recv(new_socket, buffer, 1024, 0) < 0)
		throw std::runtime_error("Error: Could not receive request from the client");

	std::cout << buffer << std::endl;
}

void	Server::parseResponse(int new_socket) {

	std::string			response;

	response.append("HTTP/1.1 200 OK\n");
	response.append("Content-Type: text/plain\n");
	response.append("Connection: keep-alive\n");
	response.append("\nSpoderman");

	if (send(new_socket, response.c_str(), response.length(), 0) < 0)
		throw std::runtime_error("Error: Could not send request to the client");
}