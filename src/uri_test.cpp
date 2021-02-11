/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uri_test.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/07 20:36:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/11 16:06:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"
#include <cstdlib>
#include <iostream>

//URI[] <- overload operator

//reference naar een part

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	URI uri(argv[1]);

	std::cout << uri.get_uri() << std::endl;
	std::cout << "SCHEME: " << uri.get_scheme() << std::endl;
	std::cout << "HOST: " << uri.get_host() << std::endl;
	std::cout << "PORT: " << uri.get_port() << std::endl;
	std::cout << "PATH: " << uri.get_path() << std::endl;
	std::cout << "QUERY: " << uri.get_query() << std::endl;
	std::cout << "FRAGMENT: " << uri.get_fragment() << std::endl;
	return (0);
}
