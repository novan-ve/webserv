/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Method.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 20:24:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 21:00:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"
#include <stdexcept>
#include <string>
#include <vector>

std::string	Method::toString()
{
	const char *types[] = {
		"OPTIONS",
		"GET",
		"HEAD",
		"POST",
		"DELETE",
		"TRACE",
		"CONNECT",
		NULL
	};
	if (this->id >= OPTIONS && this->id <= CONNECT)
		return (types[this->id]);
	else
		throw std::runtime_error("Not a valid method");
}

e_method	Method::toId()
{
	const char *types[] = {
		"OPTIONS",
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"TRACE",
		"CONNECT",
		NULL
	};
	for (size_t i = 0; i < (sizeof(types) / sizeof(char*)) - 1; i++)
		if (types[i] == this->str)
			return((e_method)i);
	throw std::runtime_error("Not a valid method");
}

Method::Method(const Method& other) : id(other.id), str(other.str) {}

Method::Method(std::string str) : str(str)
{
	this->id = this->toId();
}

Method::Method(e_method id) : id(id)
{
	this->str = this->toString();
}

Method&	Method::operator = (const Method& other)
{
	if (this != &other)
	{
		this->id = other.id;
		this->str = other.str;
	}
	return (*this);
}

Method::~Method() {}

Method::Method() {} //fuck 42s coplien
