/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 00:44:35 by tbruinem      ########   odam.nl         */
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
		Request(const std::string& requestMethod, const std::string &file_path);
		Request(const Request& other);
		Request& operator = (const Request& other);
		~Request();

		void		saveRequest(std::vector<std::string> &lines);
		void		printRequest(void) const;

		std::string	get_method(void) const;
		std::string	get_path(void) const;

	private:
		Request(); //42's "coplien" forces us to do this, ew

		std::string	method;
		std::string path;
};

#endif
