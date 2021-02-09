/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   uri_test.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/07 20:36:56 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/08 13:42:20 by tbruinem      ########   odam.nl         */
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
	std::cout << "PRINTED: " << uri[URI_HOST] << std::endl;
	uri["scheme"]("http");
	uri["host"]("google.com");
	std::cout << uri.get_uri() << std::endl;
	uri[""]("http://www.bing.com/search?query=fuck_bing");
	std::cout << uri.get_uri() << std::endl;
	return (0);
}
