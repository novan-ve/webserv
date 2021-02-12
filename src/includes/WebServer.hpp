/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:16:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/12 12:18:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEB_SERVER_HPP
# define WEB_SERVER_HPP

# include "Configuration.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Context.hpp"
# include "Request.hpp"
# include "Response.hpp"

# include <vector>
# include <map>
# include <sys/select.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

# define DEFAULT_CONFIG "./config/default.conf"

class WebServer : public Context
{
	private:
		friend class Configuration;
		friend class Context;

		WebServer();
		std::map<int, Server*>	servers;
		std::map<int, Client*>	clients; //has to be pointer so the destructor only gets called once, when it's deleted
		std::map<int, Request>	requests;
		std::map<int, Response>	responses;
		fd_set					read_sockets; //contain all sockets that need to be read from
		fd_set					write_sockets; //contains all sockets that need to be written to

		void	deleteClient(int fd);
//		Server&	newServer();
		bool	newClientAdded(fd_set& read_set);

		//to be able to have one fd_set containing all connections, clients are collected in the all-encompassing class
	public:
		WebServer(char *config_path);
		WebServer(const WebServer& other);
		void	run();
		WebServer& operator = (const WebServer& other);
		~WebServer();

		void		handle_args(std::list<std::string> args);
};

#endif
