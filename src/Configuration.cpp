/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 18:51:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 17:19:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"
#include "WebServer.hpp"
#include "Server.hpp"
#include <fcntl.h>

//open the config or revert back to the default config file
Configuration::Configuration(char *config, WebServer& webserv) : webserv(webserv)
{
	(void)config; //DELETE
}



//parse the config into Servers and presumably also global settings ?
void	Configuration::parse()
{
	addServer();
}

//interact with the webserv class to create a new Server
void	Configuration::addServer()
{
	this->webserv.newServer();
}

//close config file
Configuration::~Configuration()
{
	
}

//Configuration::Configuration() {}
