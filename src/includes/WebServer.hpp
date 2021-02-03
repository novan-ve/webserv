/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WebServer.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 14:16:49 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 15:39:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEB_SERVER_HPP
# define WEB_SERVER_HPP

# include "Configuration.hpp"
# include "Server.hpp"
# include <vector>
# include <map>

class WebServer
{
	private:
		WebServer();
		Configuration			config;
		std::vector<Server>		servers;

		//clients collected in the program class to be able to have one fd_set containing all connections
		std::map<int, Client>	clients; //int = fd
	public:
		WebServer(char *config_path);
		WebServer(const WebServer& other);
		WebServer& operator = (const WebServer& other);
		~WebServer();
};

#endif
