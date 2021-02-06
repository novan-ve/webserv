/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 12:00:57 by tbruinem      ########   odam.nl         */
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

		void		composeRequest(std::vector<std::string> &lines);
		void		printRequest(void) const;

		bool		get_has_body(void) const;
		bool		get_faulty_header(void) const;
		std::string	get_status_line(void) const;

	private:
		Request(); //42's "coplien" forces us to do this, ew
		bool		has_body;
		bool		faulty_header;
		std::string	method;
		std::string path;
		std::string status_line;
		
};

#endif
