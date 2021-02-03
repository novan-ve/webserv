/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 20:18:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include "Client.hpp"
#include <fcntl.h>

//WebServer::WebServer() {}

WebServer::~WebServer()
{
	//delete all clients
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		delete it->second;
	this->clients.clear();
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

	for (std::vector<Server>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		// if (!FD_ISSET(it->_server_fd, &this->sockets))
		// 	continue ;
		new_client_added = true;
//		int fd = accept(it->_server_fd, reinterpret_cast<struct sockaddr*>(&client_address), &client_address_len);
		int fd = open("./test", O_RDWR);
		if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
			throw std::runtime_error("Error: Could not set client-socket to O_NONBLOCK");
		new_client = new Client(*it, fd, client_address, client_address_len);
		this->clients.insert(std::pair<int, Client*>(fd, new_client));
		break ;
	}
	return (new_client_added);
}

void	WebServer::start()
{
	int		fds_ready;
	while (1)
	{
		std::cout << "I AM RUNNING" << std::endl;
		if ((fds_ready = select(this->servers.size() + this->clients.size(), &this->sockets, NULL, NULL, NULL)) == -1)
			throw std::runtime_error("Error: select() returned an error");
		std::cout << fds_ready << std::endl;
		if (fds_ready == 0) //no pending connections/requests
			continue ;
		std::cout << "yeet" << std::endl;
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
