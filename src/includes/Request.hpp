/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/16 16:19:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Request_HPP
# define Request_HPP

# include "Message.hpp"
# include "Method.hpp"
# include "URI.hpp"

# include <utility>

class Request : public Message
{
	public:
		Request();
		Request(const Request& other);
		Request& operator = (const Request& other);
		~Request();

		bool 		isStatusLine(const std::string& line);
		bool		parseLine(std::string line);
		void		splitRequest(void);
		void		printRequest(void) const;
		void		process(int fd);

		bool		get_done(void) const;
		std::string	get_method(void) const;
		std::string	get_path(void) const;
		int			get_status_code() const;
		URI							uri;

	private:
//		int							fd;
		bool						done;
		std::string 				status_line;
		std::vector<std::string>	lines;
//		std::string					method;
		std::string					path;
		int							status_code;
		Method						method;
};

#endif
