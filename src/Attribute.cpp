/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Attribute.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 10:06:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 13:07:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Scope.hpp"
#include "Attribute.hpp"

//set scope of attribute
Attribute::Attribute(Scope& scope) : scope(scope) {}

void	Attribute::handle_args(std::list<std::string> args)
{
	(void)args;
	throw std::runtime_error("Error: arguments encountered for attribute that doesnt expect arguments");
}

Attribute&	Attribute::handle_keyword(std::string key)
{
	(void)key;
	throw std::runtime_error("Error: body encountered for attribute that doesnt expect a body");
}

Attribute::~Attribute() {}
