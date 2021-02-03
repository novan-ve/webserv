/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 21:46:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "Client.hpp"
#include "WebServer.hpp"
#include "Utilities.hpp"

//WebServer::WebServer() {}

WebServer::~WebServer()
{
	//delete all clients
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		delete it->second;
	this->clients.clear();
	for (std::map<int, Server*>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
		delete it->second;
	this->servers.clear();
}

WebServer::WebServer(char *config_path) : servers(), clients(), config(config_path, *this)
{

}

bool	WebServer::newClientAdded()
{
	struct sockaddr_in	client_address;
	socklen_t			client_address_len = sizeof(client_address);
	bool				new_client_added = false;
	Client				*new_client;

	for (std::map<int, Server*>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		Server*	server = it->second;
		if (!FD_ISSET(server->_server_fd, &this->sockets))
			continue ;
		new_client_added = true;
		int fd = accept(server->_server_fd, reinterpret_cast<struct sockaddr*>(&client_address), &client_address_len);
		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Error: Could not set client-socket to O_NONBLOCK");
		new_client = new Client(*server, fd, client_address, client_address_len);
		this->clients.insert(std::pair<int, Client*>(fd, new_client));
		break ;
	}
	return (new_client_added);
}

void	WebServer::run()
{
	int		fds_ready;
	while (1)
	{
		std::cout << "I AM RUNNING" << std::endl;
		size_t		max_fd = ft::max(ft::max_element(this->servers), ft::max_element(this->clients)) + 1;
		if ((fds_ready = select(max_fd, &this->sockets, NULL, NULL, NULL)) == -1)
			throw std::runtime_error("Error: select() returned an error");
		if (fds_ready == 0) //no pending connections/requests
			continue ;
		while (this->newClientAdded()) //new connection has priority
		{
			std::cout << "NEW CLIENT ADDED" << std::endl;

			fds_ready--;
		}
		if (fds_ready) //handle existing clients
		{

		}
		return ; //DELETE
	}
}
