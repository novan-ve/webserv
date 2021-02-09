/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 21:00:20 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/09 19:13:20 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"
#include "URI.hpp"

#include <stdio.h>
#include <iostream>
#include "Utilities.hpp"

int		main(int argc, char **argv)
{
	if (argc != 1 && argc != 2)
		return (!!dprintf(2, "Wrong number of arguments!"));
	try
	{
		WebServer	webserv(argv[1]);
		webserv.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return 0;
}
