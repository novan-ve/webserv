/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:30:08 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/01 20:31:22 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <netinet/in.h>

# define PORT 8080

class Server {

public:

	Server();
	Server( const Server &src );
	Server&	operator=( const Server &rhs );
	virtual ~Server();

	void	startListening( void );
	void	parseRequest( int new_socket );
	void	parseResponse( int new_socket );

private:

	int                 _server_fd;
	struct sockaddr_in  _address;
};

void    		put_error( const std::string &str );
void   			*ft_memset( void *b, int c, size_t len );
unsigned short	ft_htons(unsigned short x);

#endif
