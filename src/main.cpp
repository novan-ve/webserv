/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:36:22 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 21:00:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include "Method.hpp"
#include <iostream>

int main(void)
{
	Method method_id(GET);
	Method method_str("HOI");

	std::cout << method_id.str << std::endl;
	std::cout << method_str.id << std::endl;
	return (0);
}
