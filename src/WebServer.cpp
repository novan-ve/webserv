/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 16:00:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/12 12:27:44 by tbruinem      ########   odam.nl         */
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

	FD_ZERO(&this->read_sockets);
	FD_ZERO(&this->write_sockets);
	Configuration	config(config_path, *this);
	config.parse();
}

void	WebServer::deleteClient(int fd)
{
	if (!this->clients.count(fd))
		throw ft::runtime_error("Could not delete client, not in 'clients'");
	delete this->clients[fd];
	this->clients.erase(fd);
	FD_CLR(fd, &this->read_sockets);
}

bool	WebServer::newClientAdded(fd_set& read_set)
{
	bool				new_client_added = false;
	int					client_fd;
	Client				*new_client;

	for (std::map<int, Server*>::iterator it = this->servers.begin(); it != this->servers.end(); it++)
	{
		Server*	server = it->second;
		if (!FD_ISSET(server->_server_fd, &read_set))
			continue ;
		new_client_added = true;
		new_client = new Client(*server);
		client_fd = new_client->getFd();
		this->clients[client_fd] = new_client;
		FD_CLR(server->_server_fd, &read_set);
		FD_SET(client_fd, &this->read_sockets);
	}
	return (new_client_added);
}

void	WebServer::run()
{
	int					fds_ready;
	std::vector<int>	closed_clients;
	fd_set				read_set;
	fd_set				write_set;

	while (1)
	{
		closed_clients.clear();
		std::cout << "I AM RUNNING" << std::endl;
		size_t		max_fd = ft::max(ft::max_element(this->servers), ft::max_element(this->clients)) + 1;
		read_set = this->read_sockets;
		write_set = this->write_sockets;
		if ((fds_ready = select(max_fd, &read_set, &write_set, NULL, NULL)) == -1)
			throw ft::runtime_error("Error: select() returned an error");
		std::cout << "FDS_READY: " << fds_ready << std::endl;
		while (this->newClientAdded(read_set)) //new connection has priority
		{
//			std::cout << "NEW CLIENT ADDED" << std::endl;
			fds_ready--;
		}
		//loop through all the clients
		for (std::map<int, Client*>::iterator it = this->clients.begin(); it != this->clients.end();)
		{
			int fd = it->first;
//			std::cout << "CLIENT FD: " << fd << std::endl;
			if (FD_ISSET(fd, &read_set))
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
					FD_SET(fd, &this->write_sockets);
					FD_CLR(fd, &this->read_sockets);
//					std::cout << "RESPONSE MADE, WAITING FOR CLIENT.." << std::endl;
				}
				it++;
			}
			//if write_set, send the response
			else if (FD_ISSET(fd, &write_set) && responses.count(fd))
			{
				std::cout << "CLIENT IS READY FOR RESPONSE" << std::endl;
				responses[fd].sendResponse(fd);
				if (responses[fd].get_status_code() != 200)
					closed_clients.push_back(fd);
				responses.erase(fd);
				FD_CLR(fd, &this->write_sockets);
				it++;
			}
			else
				it++;
//			std::cout << "CHECKING NEXT CLIENT" << std::endl;
		}
		//delete all clients that requested Connection: close or whose requests were erroneous
		std::cout << "CLOSING CLIENTS" << std::endl;
		for (size_t i = 0; i < closed_clients.size(); i++)
		{
			std::cout << "DELETING CLIENT: " << closed_clients[i] << std::endl;
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
