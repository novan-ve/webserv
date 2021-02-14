/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:12:31 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/12 00:52:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <map>
# include "Request.hpp"

class Response : public Message
{
	public:
		Response();
		Response(const Response& other);
		Response& operator = (const Response& other);
		~Response();

		void	sendResponse(int fd) const;
		void	printResponse(void) const;
		void	composeResponse(void);
		void	setRequest(Request& req);
		int		get_status_code() const;

	private:
		Request						req;
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
		void	listDirectory(void);
		void	setContentLen(void);
		void	setModified(void);
};

#endif
