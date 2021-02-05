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

# include "Request.hpp"

class Response : public Message
{
	public:
		Response(Request *request);
		Response(const Response& other);
		Response& operator = (const Response& other);
		~Response();

		void		composeResponse(void);
		void		sendResponse(int fd) const;
		void		printResponse(void) const;

		std::string	getTime(void) const;

	private:
		Response();
		Request*	req;
		std::string	status_line;
		int			code;
};

#endif
