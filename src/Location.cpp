/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:22:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 01:26:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Context.hpp"
#include "Attribute.hpp"

Location::Location() {}

Location::Location(const Location& other) : Context() { (void)other; }

void	Location::handle_args(std::list<std::string> args)
{
	std::cout << "ARGS" << std::endl;
	ft::print_iteration(args.begin(), args.end());
}
