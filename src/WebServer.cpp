/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 02:19:25 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

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

void	WebServer::deleteClient(int fd)
{
	if (!this->clients.count(fd))
		throw std::runtime_error("Could not delete client, not in 'clients'");
	this->clients.erase(fd);
	FD_CLR(fd, &this->sockets);
}

bool	WebServer::newClientAdded()
{
	bool				new_client_added = false;
	int					client_fd;
	Client				*new_client;

	for (std::map<int, Server*>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		Server*	server = it->second;
		if (!FD_ISSET(server->_server_fd, &this->set_sockets))
			continue ;
		new_client_added = true;
		new_client = new Client(*server);
		client_fd = new_client->getFd();
		this->clients[client_fd] = new_client;
		FD_SET(client_fd, &this->sockets);
		//We might be missing a step, using connect() and the setup that it requires.
		server->parseRequest(client_fd);
		server->parseResponse(client_fd);
		this->deleteClient(client_fd);
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
		this->set_sockets = this->sockets;
		if ((fds_ready = select(max_fd, &this->set_sockets, NULL, NULL, NULL)) == -1)
			throw std::runtime_error("Error: select() returned an error");
		sleep(1);
		if (fds_ready == 0) //no pending connections/requests
		{
			std::cout << "No connection, sleeping for 3 seconds" << std::endl;
			continue ;
		}
		if (this->newClientAdded()) //new connection has priority
		{
			std::cout << "NEW CLIENT ADDED" << std::endl;

			fds_ready--;
		}
		// if (fds_ready) //handle existing clients
		// {

		// }
	}
}
