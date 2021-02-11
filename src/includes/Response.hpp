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

		void	sendResponse(int fd) const;
		void	printResponse(void) const;
		void	composeResponse(void);

	private:
		Request*					req;
		std::map<int, std::string>	status_codes;
		std::string					status_line;
		std::string					path;
		int							response_code;

		void	checkPath(void);

		void	setStatusLine(void);
		void	setServer(void);
		void	setDate(void);
		void	setContentType(void);
		void	setBody(void);
		void	setBodyError(void);
		void	setContentLen(void);
		void	setModified(void);

		Response();
};

#endif
