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
		Request(std::vector<std::string> &lines);
		//Request(Method method, char *path, int version);
		Request(const Request& other);
		Request& operator = (const Request& other);
		~Request();
		void	printRequest(void) const;

		bool		get_has_body(void) const;
		bool		get_faulty_header(void) const;
		std::string	get_status_line(void) const;
	//	void	send(int fd) const;
	private:
		Request(); //42's "coplien" forces us to do this, ew
		bool		has_body;
		bool		faulty_header;
		std::string status_line;
		
};

#endif
