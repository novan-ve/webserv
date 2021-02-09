/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Client.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 17:36:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 15:19:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

//Client::Client() {}

Client::Client(Server& server) : server(server)
{
	this->fd = accept(server._server_fd, reinterpret_cast<struct sockaddr*>(&this->address), &this->addr_len);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error: Could not set client-socket to O_NONBLOCK");
}

int		Client::getFd()
{
	return (this->fd);
}

int		Client::handleRequest()
{
	return (this->server.handleRequest(this->fd));
}

Client::Client(const Client& other) : server(other.server), address(other.address), addr_len(other.addr_len), fd(other.fd) {}

Client::~Client()
{
	std::cout << "CLIENT DESTRUCTOR CALLED" << std::endl;
	close(this->fd);
}

//private garbage
//Client&	Client::operator = (const Client& other) {}
//Client::Client() : server() {} //impossible, because no Server& is given
