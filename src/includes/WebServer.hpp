/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:16:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/05 13:10:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEB_SERVER_HPP
# define WEB_SERVER_HPP

# include "Configuration.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include <vector>
# include <map>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define DEFAULT_CONFIG "./config/default.conf"

class WebServer
{
	private:
		friend class Configuration;

		WebServer();
		std::map<int, Server*>	servers;
		std::map<int, Client*>	clients; //has to be pointer so the destructor only gets called once, when it's deleted
		fd_set					sockets; //contain all sockets
		fd_set					set_sockets; //first: copy of sockets, after select(): contains only sockets with activity

		void	deleteClient(int fd);
		void	newServer();
		bool	newClientAdded();

		//to be able to have one fd_set containing all connections, clients are collected in the all-encompassing class
	public:
		WebServer(char *config_path);
		WebServer(const WebServer& other);
		void	run();
		WebServer& operator = (const WebServer& other);
		~WebServer();
};

#endif
