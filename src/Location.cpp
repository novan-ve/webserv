/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:22:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 23:08:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Context.hpp"

//Location is a child Context of Server
Location::Location(Context& parent) : Context(parent)
{
	this->type = "Location";
	this->keywords.push_back("limit_except");
	this->keywords.push_back("root");
	this->keywords.push_back("autoindex");
	std::cout << "LOCATION CREATED!" << std::endl;
}

Location::~Location()
{
	std::cout << "LOCATION DECONSTRUCTED" << std::endl;
}

Location::Location(const Location& other) : Context(other.parent) {}

void	Location::handle_args(std::list<std::string> args)
{
	std::cout << "Location ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}
