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
		Request();
		Request(const Request& other);
		Request& operator = (const Request& other);
		~Request();

		int 		isStatusLine(const std::string& line);
		void		parseLine(std::string line);
		void		splitRequest(void);
		void		printRequest(void) const;

		bool		get_done(void) const;
		std::string	get_method(void) const;
		std::string	get_path(void) const;

	private:
		bool						done;
		std::string 				status_line;
		std::vector<std::string>	lines;
		std::string					method;
		std::string					path;
};

#endif
