/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:30:08 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/16 01:58:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <netinet/in.h>
# include <string>
# include <list>
# include <vector>

# include "Context.hpp"
# include "Utilities.hpp"
# include "Request.hpp"
# include "Location.hpp"
# include "Utilities.hpp"

//# define PORT 8080

class Server : public Context
{
	public:
//		Server();
		Server(Context& parent);
		Server( const Server &src );
		Server&	operator=( const Server &rhs );
		~Server();
		void	init();

		void	startListening( void );
		int		acceptNewClient();

		void	handle_args(std::list<std::string> args);

		std::map<std::string, Location*, ft::size_compare>	locations;
		int									_server_fd;

	private:
		struct sockaddr_in			_address;
};

#endif
