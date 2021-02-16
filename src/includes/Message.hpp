/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Message.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:08:13 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/16 11:48:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <vector>
#include <string>
#include <utility>
#include <map>

//virtual base class for Response/Request
class Message
{
	public:
		Message();
		Message(const Message& other);
		Message& operator = (const Message& other);
		virtual ~Message();
		const std::map<std::string, std::string>&	get_headers();
	protected:
		std::map<std::string, std::string>					headers;
		std::vector<std::string>							body;
};

#endif
