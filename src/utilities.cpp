/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:29:21 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/01 20:29:22 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>

void    put_error(const std::string &str) {

	std::cout << "Webserv: " << str << std::endl;
	exit(EXIT_FAILURE);
}

void    *ft_memset(void *b, int c, size_t len)
{
	unsigned char   *str;

	str = static_cast<unsigned char*>(b);
	while (len > 0)
	{
		*str = c;
		str++;
		len--;
	}
	return (b);
}

unsigned short	ft_htons(unsigned short x) {

	return ((((x) >> 8) & 0xff ) | (((x) & 0xff) << 8));
}
