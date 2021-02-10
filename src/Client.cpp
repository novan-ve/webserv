/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Client.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 17:36:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/10 18:21:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "includes/Exception.hpp"
#include "includes/Response.hpp"

//Client::Client() {}

Client::Client(Server& server) : server(server), req(NULL)
{
	this->fd = accept(server._server_fd, reinterpret_cast<struct sockaddr*>(&this->address), &this->addr_len);
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("Error: Could not set client-socket to O_NONBLOCK");
}

int		Client::getFd()
{
	return (this->fd);
}

void	Client::handleResponse(int code) {

	Response	resp(this->req, code);

	resp.composeResponse();
	resp.printResponse();
	resp.sendResponse(this->fd);

	if (this->req) {
		delete this->req;
		this->req = NULL;
	}
}

int		Client::handleRequest()
{
	std::vector <std::string> lines_read = ft::get_lines(this->fd);

	if (!this->req)
		req = new Request;

	for (std::vector<std::string>::iterator it = lines_read.begin(); it != lines_read.end(); it++) {
		std::cout << "REQUEST: " << *it << std::endl;
		try {
			req->parseLine(*it);
			if (req->get_done()) {
				this->handleResponse(200);
				if (lines_read.size() == 1)
					return 0;
				return 1;
			}
			if (lines_read.size() == 1)
				return 0;
		}
		catch (ft::reqException &e) {
			this->handleResponse(e.getCode());
			return 1;
		}
	}
	std::cout << "If you read this, something went wrong in Client::handleRequest()" << std::endl;
	return 1;
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
