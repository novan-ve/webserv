/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 18:51:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 20:07:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"
#include "WebServer.hpp"
#include "Server.hpp"
#include <fcntl.h>

Configuration::Configuration(char *config, WebServer& webserv) : webserv(webserv)
{
	(void)config; //DELETE
	FD_ZERO(&this->webserv.sockets);
	addServer();
}

void	Configuration::addServer()
{
	Server	new_server = Server();
	this->webserv.servers.push_back(new_server);
	FD_SET(new_server._server_fd, &this->webserv.sockets);
}

//Configuration::Configuration() {}
