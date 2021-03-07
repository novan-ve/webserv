/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/28 16:40:48 by tbruinem      ########   odam.nl         */
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
		int			get_status_code(void) const;
		std::map<std::string, std::string>& get_headers(void);
		std::vector<std::string>&	get_body(void);
		URI							uri;

	private:
		bool		isMethod(std::string str);
//		int							fd;
		bool						done;
		std::string 				status_line;
		std::vector<std::string>	lines;
//		std::string					method;
		std::string					path;
		int							status_code;
		Method						method;
		int							body_read;
		int							body_total;
		bool						body_started;
		bool						encoding;
};

#endif
