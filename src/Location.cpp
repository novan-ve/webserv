/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:22:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 13:13:17 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Scope.hpp"

//Location is a child scope of Server
Location::Location(Scope& parent) : Scope(parent)
{
	std::cout << "LOCATION CREATED!" << std::endl;
}

Location::~Location()
{
	std::cout << "LOCATION DECONSTRUCTED" << std::endl;
}

Location::Location(const Location& other) : Scope() { (void)other; }

void	Location::handle_args(std::list<std::string> args)
{
	std::cout << "ARGS" << std::endl;
	ft::print_iteration(args.begin(), args.end());
}
