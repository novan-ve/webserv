/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utilities.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 21:38:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 01:00:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include <map>
#include <limits>
#include <string>
#include <vector>
#include <iostream>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

namespace ft
{
	template <class T1, class T2>
	size_t	max_element(const std::map<T1,T2>& container)
	{
		typename std::map<T1,T2>::const_reverse_iterator it;
		if (!container.size() || (it = container.rbegin()) == container.rend())
			return (0);
		return (it->first);
	}

	template <class T>
	T	max(T a, T b)
	{
		return ((a > b) ? a : b);
	}

	template <class Iter>
	void	print_iteration(Iter first, Iter last, std::string delim = ",")
	{
		for (; first != last;)
			std::cout << *first << ((++first == last) ? "\n" : delim);	
	}

	void	put_error(const std::string &str);

	void	*memset(void *b, int c, size_t len);

	unsigned short	htons(unsigned short x);

	std::vector<std::string>	get_lines(int fd, size_t max_lines = std::numeric_limits<size_t>::max());

	std::vector<std::string>	split(std::string raw, std::string delim, std::string preserve_delim = "");
}

#endif
