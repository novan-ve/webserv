/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 16:21:50 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/28 14:03:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "Exception.hpp"
#include <vector>
#include <arpa/inet.h>

#include "Server.hpp"
#include "Utilities.hpp"
#include "Location.hpp"
#include "Context.hpp"

//Context - WebServer, Server is a child Context of WebServer
Server::Server(Context& parent) : Context(parent)
{
	this->keywords.push_back("location");
	this->keywords.push_back("listen");
	this->keywords.push_back("server_name");
	this->keywords.push_back("error_page");
	this->keywords.push_back("client_max_body_size");
	this->keywords.push_back("cgi_param");
	this->keywords.push_back("auth_basic");
	this->keywords.push_back("auth_basic_user_file");
}

bool	Server::init()
{
	int 	opt = 1;

	std::cout << "IP: " << this->properties.ip_port.first << " | PORT: " << this->properties.ip_port.second << std::endl;

	// Create socket file descriptor
	if ((this->_server_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		throw ft::runtime_error("Error: Creation of socket failed");

	// Forcefully attach socket to port
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
		throw ft::runtime_error("Error: Failed to set socket options");

	// Assign transport address
	this->_address.sin_family = AF_INET;
	if (this->properties.ip_port.first == "localhost")
		this->properties.ip_port.first = "127.0.0.1";
	this->_address.sin_addr.s_addr = (this->properties.ip_port.first == "0.0.0.0") ? INADDR_ANY : inet_addr(this->properties.ip_port.first.c_str());
	this->_address.sin_port = ft::host_to_network_short(ft::stoi(this->properties.ip_port.second));
	ft::memset(this->_address.sin_zero, '\0', sizeof(this->_address.sin_zero));

	// Attach socket to transport address
	if (bind(this->_server_fd, reinterpret_cast<struct sockaddr*>(&this->_address), sizeof( this->_address )) == -1)
	{
//		throw ft::runtime_error("Error: binding server-socket to a port failed");
		return false;
	}

	if (listen(this->_server_fd, 10 ) == -1)
		throw ft::runtime_error("Error: could not set server-socket to listening mode");
	std::cout << "SERVER CREATED!" << std::endl;

	//Set the resulting socketfd to be non blocking
	if (fcntl(this->_server_fd, F_SETFL, O_NONBLOCK) == -1)
		throw ft::runtime_error("Error: Could not set server-socket to O_NONBLOCK");

	// for (std::map<std::string, Location*>::iterator it = this->locations.begin(); it != locations.end(); it++)
	// {
	// 	std::cout << "LOCATION: " << it->first << std::endl;
	// }
	return true;
}

Server::Server(const Server &src)
{
	*this = src;
}

Server&		Server::operator=(const Server &rhs)
{
	if (this != &rhs)
	{
		this->_server_fd = rhs._server_fd;
		this->_address = rhs._address;
		this->keywords = rhs.keywords;
	}
	return *this;
}

Server::~Server()
{
	std::cout << "DECONSTRUCTING SERVER" << std::endl;
	close(this->_server_fd);
}

void	Server::handle_args(std::list<std::string>	args)
{
	std::cout << "Server ARGS: ";
	ft::print_iteration(args.begin(), args.end());
	if (args.size())
		throw ft::runtime_error("Error: Configuration error encountered in 'server'");
	return ;
}
