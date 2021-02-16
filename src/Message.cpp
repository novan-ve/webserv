/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Message.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/16 15:00:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"
#include <iostream>

Message::Message() {}

Message::Message(const Message& other) {

	*this = other;
}

Message& Message::operator = (const Message& other)
{
	if (this != &other)
	{
		this->body = other.body;
		this->headers = other.headers;
	}
	return (*this);
}

std::string	Message::get_header(const std::string& key)
{
	if (this->headers.count(key))
		return (this->headers[key]);
	else
		return "";
}

Message::~Message() {}
