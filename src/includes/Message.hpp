/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Message.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:08:13 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 20:16:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <vector>
#include <string>
#include <utility>

//virtual base class for Response/Request
class Message
{
	public:
		Message();
		Message(const Message& other);
		Message& operator = (const Message& other);
		virtual ~Message();
		virtual void	send(int fd) const = 0;
	protected:
		std::vector<std::pair<std::string, std::string> >	headers;
		std::vector<std::string>							body;
};

#endif
