/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 18:51:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 21:23:44 by tbruinem      ########   odam.nl         */
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
	Server*	new_server = new Server();
	this->webserv.servers.insert(std::pair<int, Server*>(new_server->_server_fd, new_server));
	FD_SET(new_server->_server_fd, &this->webserv.sockets);
}

//Configuration::Configuration() {}
