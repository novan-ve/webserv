/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/12 01:24:01 by tbruinem      ########   odam.nl         */
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
	this->keywords.push_back("server");

	FD_ZERO(&this->sockets);
	Configuration	config(config_path, *this);
	config.parse();
}

void	WebServer::deleteClient(int fd)
{
	if (!this->clients.count(fd))
		throw ft::runtime_error("Could not delete client, not in 'clients'");
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
		if (!FD_ISSET(server->_server_fd, &this->set_read_sockets))
			continue ;
		new_client_added = true;
		new_client = new Client(*server);
		client_fd = new_client->getFd();
		this->clients[client_fd] = new_client;
		FD_CLR(server->_server_fd, &this->set_read_sockets);
		FD_SET(client_fd, &this->sockets);
	}
	return (new_client_added);
}



void	WebServer::run()
{
	int					fds_ready;
	std::vector<int>	closed_clients;

	while (1)
	{
		closed_clients.clear();
		std::cout << "I AM RUNNING" << std::endl;
		size_t		max_fd = ft::max(ft::max_element(this->servers), ft::max_element(this->clients)) + 1;
		this->set_read_sockets = this->sockets;
		this->set_write_sockets = this->sockets;
		if ((fds_ready = select(max_fd, &this->set_read_sockets, &set_write_sockets, NULL, NULL)) == -1)
			throw ft::runtime_error("Error: select() returned an error");
		while (this->newClientAdded()) //new connection has priority
		{
			std::cout << "NEW CLIENT ADDED" << std::endl;
			fds_ready--;
		}
		//loop through all the clients
		for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end();)
		{
			int fd = it->first;
			std::cout << "CLIENT FD: " << fd << std::endl;
			if (FD_ISSET(fd, &this->set_read_sockets))
			{
				//create the request if it doesn't exist.
				if (!requests.count(fd))
					requests.insert(std::pair<int, Request>(fd, Request()));
				requests[fd].process(fd);
				if (requests[fd].get_done())
				{
					responses[fd] = Response();
					responses[fd].setRequest(requests[fd]);
					responses[fd].composeResponse();
					responses[fd].printResponse();
					requests.erase(fd);
					std::cout << "RESPONSE MADE, WAITING FOR CLIENT.." << std::endl;
				}
				FD_CLR(fd, &this->set_read_sockets);
				it++;
			}
			//if write_set, send the response
			else if (FD_ISSET(fd, &this->set_write_sockets) && responses.count(fd))
			{
				std::cout << "CLIENT IS READY FOR RESPONSE" << std::endl;
				responses[fd].sendResponse(fd);
				if (responses[fd].get_status_code() != 200)
					closed_clients.push_back(fd);
				responses.erase(fd);
				FD_CLR(fd, &this->set_write_sockets);
				it++;
			}
			else
				it++;
			std::cout << "CHECKING NEXT CLIENT" << std::endl;
		}
		//delete all clients that requested Connection: close or whose requests were erroneous
		std::cout << "CLOSING CLIENTS" << std::endl;
		for (size_t i = 0; i < closed_clients.size(); i++)
		{
			delete clients[closed_clients[i]];
			clients.erase(closed_clients[i]);
		}
		std::cout << "END OF RUN LOOP BODY\n";
	}
}

void	WebServer::handle_args(std::list<std::string>	args)
{
	std::cout << "ARGS" << std::endl;
	ft::print_iteration(args.begin(), args.end());
	if (args.size())
		throw ft::runtime_error("Error: Configuration error encountered in 'webserver'");
	return ;
}
