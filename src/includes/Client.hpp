/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Client.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 15:24:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/11 23:57:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

class Client
{
	private:
		Server*					server;
		struct sockaddr_in		address;
		socklen_t				addr_len;
		Request					*req;
		Client();
		Client& operator = (const Client& other);
		int						fd;
	public:
		int		getFd();
		Client(Server* server);
		Client(const Client& other);
		virtual ~Client();
};

#endif
