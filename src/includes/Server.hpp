/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:30:08 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/03 21:47:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <netinet/in.h>

# include "Utilities.hpp"
# include "Request.hpp"

# define PORT 8080

class Server {

public:

	Server();
	Server( const Server &src );
	Server&	operator=( const Server &rhs );
	~Server();

	void	startListening( void );
	void	parseRequest( int new_socket );
	void	parseResponse( int new_socket, Request *req );
	int		acceptNewClient();
	int					_server_fd;

private:

	struct sockaddr_in	_address;
};

#endif
