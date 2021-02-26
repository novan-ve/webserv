/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:22:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/26 13:34:19 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Context.hpp"

//impossible
//Location::Location() {}

//Location is a child Context of Server
Location::Location(Context& parent, const std::string& location) : Context(parent), location(location)
{
	this->keywords.push_back("limit_except");
	this->keywords.push_back("root");
	this->keywords.push_back("autoindex");
	this->keywords.push_back("error_page");
	this->keywords.push_back("php-cgi");
	this->keywords.push_back("cgi_param");
	std::cout << "LOCATION CREATED!" << std::endl;
}

Location::~Location()
{
	std::cout << "LOCATION DECONSTRUCTED" << std::endl;
}

std::string	Location::get_location() const
{
	return (this->location);
}

// void		Location::set_location(const std::string& location)
// {
// 	this->location = location;
// }

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
