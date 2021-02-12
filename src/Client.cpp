/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Client.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 17:36:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/12 01:23:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <string.h>

#include "includes/Exception.hpp"
#include "includes/Response.hpp"

//Client::Client() {}

Client::Client(Server& server) : server(server)
{
	ft::memset(&this->address, '\0', sizeof(this->address));
	this->addr_len = sizeof(this->address);
	this->fd = accept(server._server_fd, (struct sockaddr*)&this->address, &this->addr_len);
	if (this->fd == -1)
	{
		std::cout << strerror(errno) << std::endl;
		throw ft::runtime_error("Error: failed to open a new client connection");
	}
	if (fcntl(this->fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << strerror(errno) << std::endl;
		throw ft::runtime_error("Error: Could not set client-socket to O_NONBLOCK");
	}
}

int		Client::getFd()
{
	return (this->fd);
}

// void	Client::handleResponse(int code) {

// 	Response	resp(this->req, code);

// 	resp.composeResponse();
// 	resp.printResponse();
// 	resp.sendResponse(this->fd);

// 	if (this->req) {
// 		delete this->req;
// 		this->req = NULL;
// 	}
// }

Client::Client(const Client& other) : server(other.server), address(other.address), addr_len(other.addr_len), fd(other.fd) {}

Client::~Client()
{
	std::cout << "CLIENT DESTRUCTOR CALLED" << std::endl;
	close(this->fd);
}

//private garbage
//Client&	Client::operator = (const Client& other) {}
//Client::Client() : server() {} //impossible, because no Server& is given
