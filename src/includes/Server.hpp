/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:30:08 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/06 17:03:02 by tbruinem      ########   odam.nl         */
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
# include "Attribute.hpp"
# include "Utilities.hpp"
# include "Location.hpp"

# define PORT 8080

class Server : public Context
{
	public:
//		Server();
		Server(Context& parent);
		Server( const Server &src );
		Server&	operator=( const Server &rhs );
		~Server();

		void	startListening( void );
		void	parseRequest( int new_socket );
		void	parseResponse( int new_socket );
		int		acceptNewClient();
		int					_server_fd;

		void	handle_args(std::list<std::string> args);

	private:
		std::vector<Location*>	locations;
		struct sockaddr_in		_address;
};

#endif
