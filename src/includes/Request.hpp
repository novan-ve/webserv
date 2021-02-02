/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 21:03:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Request_HPP
# define Request_HPP

# include "Message.hpp"
# include "Method.hpp"
# include <utility>

class Request : public Message
{
	public:
		Request(Method method, char *path, int version);
		Request(const Request& other);
		Request& operator = (const Request& other);
		~Request();
		void	send(int fd) const;
	private:
		Request(); //42's "coplien" forces us to do this, ew
		Method	method;
};

#endif
