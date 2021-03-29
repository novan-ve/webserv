/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/26 17:47:23 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#include "Client.hpp"
#include "WebServer.hpp"
#include "Utilities.hpp"
#include "Context.hpp"

WebServer::WebServer() {}

WebServer::WebServer(const WebServer & other)
{
	*this = other;
}

WebServer&	WebServer::operator=(const WebServer & other)
{
	if (this != &other)
	{
		this->servers = other.servers;
		this->clients = other.clients;
		this->requests = other.requests;
		this->responses = other.responses;
		this->read_sockets = other.read_sockets;
		this->write_sockets = other.write_sockets;
		this->server_names = other.server_names;
	}

	return *this;
}

//servers are Context*s stored in 'children' inherited Context
WebServer::~WebServer()
{
	//delete all clients
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
		delete it->second;
	this->clients.clear();
	this->servers.clear(); //deleted by Context destructor
}

WebServer::WebServer(char *config_path) : Context(), servers(), clients(), finished(true)
{
	this->keywords.push_back("server");

	FD_ZERO(&this->read_sockets);
	FD_ZERO(&this->write_sockets);
	Configuration	config(config_path, this);
	config.parse();

	for (size_t i = 0 ; i < this->children.size(); i++)
	{
		Server *current_server =  reinterpret_cast<Server*>(this->children[i]);
		this->server_names[current_server] = this->properties.server_names;
		if (current_server->init())
		{
			FD_SET(current_server->_server_fd, &this->read_sockets);
			this->servers[current_server->_server_fd] = current_server;
		}
	}
	if (this->servers.empty())
		throw std::runtime_error("Error: All of the specified servers failed to initialize");
}

void	WebServer::deleteClient(int fd)
{
	if (!this->clients.count(fd))
		throw std::runtime_error("Error: Could not delete client, not in 'clients'");
	delete this->clients[fd];
	this->clients.erase(fd);
	FD_CLR(fd, &this->read_sockets);
	FD_CLR(fd, &this->write_sockets);
}

void	WebServer::addNewClients()
{
	int					client_fd;
	Client				*new_client;

	for (std::map<int, Server*>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		Server*	server = it->second;
		if (!FD_ISSET(server->_server_fd, &this->read_set))
			continue ;
		new_client = new Client(server);
		client_fd = new_client->getFd();
		this->clients[client_fd] = new_client;
		FD_SET(client_fd, &this->read_sockets);
	}
}

WebServer*	thisCopy;
void	WebServer::closeSignal(int status)
{
	std::cout << "Received stop signal" << std::endl;

	for (std::map<int, Client*>::iterator it = thisCopy->clients.begin(); it != thisCopy->clients.end(); it++)
		delete it->second;
	thisCopy->clients.clear();
	thisCopy->servers.clear();

	FD_ZERO(&thisCopy->read_sockets);
	FD_ZERO(&thisCopy->write_sockets);

	std::cout << "Server stopped cleanly" << std::endl;

	exit(status);
}

void	WebServer::handleRead()
{
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end() && this->finished;)
	{
		int fd = it->first;
		if (FD_ISSET(fd, &this->read_set)) {
			if (!requests[fd].size())
				requests[fd].push(Request());
			Request &current_request = requests[fd].front();
			current_request.process(fd);
			if (current_request.get_done()) {
				responses[fd].push(Response());
				Response &current_response = responses[fd].back();
				current_response.setRequest(requests[fd].front());
				current_response.location_match(this->server_names);
				current_response.composeResponse();
				requests[fd].pop();
				if (requests[fd].empty())
					FD_CLR(fd, &this->read_sockets);
				FD_SET(fd, &this->write_sockets);
			}
		}
		it++;
	}
}

void	WebServer::handleWrite()
{
	for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end();)
	{
		int fd = it->first;
		if (FD_ISSET(fd, &this->write_set))
		{
			Response& current_response = responses[fd].front();
			current_response.sendResponse(fd);
			if ((this->finished = current_response.getFinished()))
			{
				if (current_response.get_status_code() != 400)
					std::cout << "[" << current_response.get_status_code() << "] Response send!" << std::endl;
				if (current_response.get_status_code() == 400 || current_response.get_status_code() == 505)
					this->closed_clients.push_back(fd);
				responses[fd].pop();
				if (responses[fd].empty())
				{
					FD_CLR(fd, &this->write_sockets);
					FD_SET(fd, &this->read_sockets);
				}
			}
			else
				break;
		}
		it++;
	}
}

void	WebServer::run()
{
	thisCopy = this;
	signal(SIGINT, WebServer::closeSignal);
	signal(SIGPIPE, Response::setSigpipe);

	this->finished = true;

	while (1)
	{
		size_t		max_fd = ft::max(ft::max_element(this->servers), ft::max_element(this->clients)) + 1;

		this->closed_clients.clear();
		this->read_set = this->read_sockets;
		this->write_set = this->write_sockets;

		if (select(max_fd, &this->read_set, &this->write_set, NULL, NULL) == -1)
			throw std::runtime_error("Error: select() returned an error");

		this->addNewClients();
		this->handleWrite();
		this->handleRead();

		for (size_t i = 0; i < this->closed_clients.size(); i++)
			this->deleteClient(this->closed_clients[i]);
	}
}
