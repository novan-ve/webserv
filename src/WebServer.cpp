/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/07 01:51:06 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "Client.hpp"
#include "WebServer.hpp"
#include "Utilities.hpp"
#include "Context.hpp"

//WebServer::WebServer() {}

//servers are Context*s stored in 'children' inherited Context
WebServer::~WebServer()
{
	//delete all clients
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		delete it->second;
	this->clients.clear();
	this->servers.clear();
}

WebServer::WebServer(char *config_path) : Context(), servers(), clients()
{
	this->type = "WebServer";
	this->keywords.push_back("server");

	FD_ZERO(&this->sockets);
	Configuration	config(config_path, *this);
	config.parse();
}

// Server&	WebServer::newServer()
// {
// 	//deprecated, done by attributeSpawner now
// 	Server*	new_server = new Server(*this);
// 	this->servers.insert(std::pair<int, Server*>(new_server->_server_fd, new_server));
// 	FD_SET(new_server->_server_fd, &this->sockets); //<- MOVE to Configuration
// 	return (*new_server);
// }

void	WebServer::deleteClient(int fd)
{
	if (!this->clients.count(fd))
		throw std::runtime_error("Could not delete client, not in 'clients'");
	delete this->clients[fd];
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
		FD_CLR(server->_server_fd, &this->set_sockets);
		FD_SET(client_fd, &this->sockets);
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
		if (fds_ready == 0) //no pending connections/requests
		{
			std::cout << "No connection, sleeping for 3 seconds" << std::endl;
			continue ;
		}
		while (this->newClientAdded()) //new connection has priority
		{
			std::cout << "NEW CLIENT ADDED" << std::endl;

			fds_ready--;
		}
		for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end();)
		{
			Client *client = it->second;

			if (!FD_ISSET(it->first, &this->set_sockets))
			{
				it++;
				continue ;
			}
			client->handleRequest();
			this->deleteClient((it++)->first);
		}
	}
}

void	WebServer::handle_args(std::list<std::string>	args)
{
	std::cout << "ARGS" << std::endl;
	ft::print_iteration(args.begin(), args.end());
	if (args.size())
		throw std::runtime_error("Error: Configuration error encountered in 'webserver'");
	return ;
}

#include "Attribute.hpp"
