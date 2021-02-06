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
	int		acceptNewClient();

	int		isStatusLine(const std::string &line);

	int		handleRequest( int new_socket );
	int		parseRequest( const std::string &line, int new_socket );
	void	handleResponse( int new_socket, Request *req );
	int		errorResponse( int status_code, int new_socket );

	int					_server_fd;

private:

	struct sockaddr_in			_address;
	std::string					_status_line;
	std::vector<std::string>	_lines;

};

#endif
