/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 19:18:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <map>
# include "Request.hpp"

class Response : public Message
{
	public:
		Response(Request *request, int code);
		Response(const Response& other);
		Response& operator = (const Response& other);
		~Response();

		std::string	getBodyLength(void) const;
		void		setBodyError(void);
		void		setContentType(std::string path);
		void		setModified(void);
		void		readPath(void);

		void		composeResponse(void);
		void		sendResponse(int fd) const;
		void		printResponse(void) const;

	private:
		Response();
		Request*					req;
		std::map<int, std::string>	status_codes;
		std::string					status_line;
		int							response_code;
		std::string					path;
};

#endif
