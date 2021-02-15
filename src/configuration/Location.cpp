/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:22:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/15 15:16:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Context.hpp"

//impossible
//Location::Location() {}

//Location is a child Context of Server
Location::Location(Context& parent) : Context(parent)
{
	this->keywords.push_back("limit_except");
	this->keywords.push_back("root");
	this->keywords.push_back("autoindex");
	std::cout << "LOCATION CREATED!" << std::endl;
}

Location::~Location()
{
	std::cout << "LOCATION DECONSTRUCTED" << std::endl;
}

// Location& Location::operator = (const Location& other)
// {
// 	if (this != &other)
// 	{
// 		this->keywords = other.keywords;
// 		this->parent = other.parent;
// 		this->children = other.children;
// 		this->properties = other.properties;
// 	}
// 	return (*this);
// }

Location::Location(const Location& other) : Context(other.parent) {}
