/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Client.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 17:36:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 19:28:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

//Client::Client() {}

Client::Client(Server& server, int fd, struct sockaddr_in address, socklen_t len) : server(server), address(address), addr_len(len), fd(fd) {}

Client::Client(const Client& other) : server(other.server), address(other.address), addr_len(other.addr_len), fd(other.fd) {}

Client::~Client()
{
	std::cout << "CLIENT DESTRUCTOR CALLED" << std::endl;
}

//private garbage
//Client&	Client::operator = (const Client& other) {}
//Client::Client() : server() {} //impossible, because no Server& is given
