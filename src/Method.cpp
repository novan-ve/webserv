/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Method.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 20:24:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/11 10:46:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Method.hpp"
#include "Exception.hpp"
#include <string>
#include <vector>

const char * const Method::names[] = {
	[OPTIONS] = "OPTIONS",
	[GET] = "GET",
	[HEAD] = "HEAD",
	[POST] = "POST",
	[PUT] = "PUT",
	[DELETE] = "DELETE",
	[TRACE] = "TRACE",
	[CONNECT] = "CONNECT"
};

Method::Method(const Method& other) : EnumString(other) {}

Method::Method(std::string str) : EnumString(str, names, sizeof(names)) {}

Method::Method(e_method id) : EnumString(id, names, sizeof(names)) {}

Method&	Method::operator = (const Method& other)
{
	// if (this != &other)
	// {
	// 	this->id = other.id;
	// 	this->str = other.str;
	// }
	return (*this);
}

Method::~Method() {}

Method::Method() : EnumString() {} //fuck 42s coplien
