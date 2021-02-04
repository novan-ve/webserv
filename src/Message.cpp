/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Message.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 18:01:23 by tbruinem      ########   odam.nl         */
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

Message::~Message() {}
