/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Request.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:37:38 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 14:14:12 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <iostream>

Request::Request() : method(GET) {}

Request::Request(const Request& other) : method(other.method) {}

Request& Request::operator = (const Request& other)
{
	if (this != &other)
	{
//		this->method = other.method;
	}
	return (*this);
}

Request::~Request() {}

void	Request::send(int fd) const
{

}
