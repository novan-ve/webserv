/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utilities.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 21:38:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/28 19:26:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include <map>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

namespace ft
{
	std::string	itos(int num, const std::string base = "0123456789");

	int stoi(std::string number, const std::string base = "0123456789");
	size_t stoul(std::string number, const std::string base = "0123456789");

	template <class T1, class T2>
	T1	max_element(const std::map<T1,T2>& container)
	{
		typename std::map<T1,T2>::const_reverse_iterator it;
		if (!container.size() || (it = container.rbegin()) == container.rend())
			return (T1());
		return (it->first);
	}
	template <class T1>
	T1	max_element(const std::vector<T1>& container)
	{
		typename std::vector<T1>::const_reverse_iterator it;
		if (!container.size() || (it = container.rbegin()) == container.rend())
			return (T1());
		return (std::max_element(container.begin(), container.end()));
	}

	template <class T>
	T	max(T a, T b)
	{
		return ((a > b) ? a : b);
	}

	template <class Iter>
	void	print_iteration(Iter first, Iter last, std::string delim = ",")
	{
		size_t distance = std::distance(first, last);
		for (; first != last;)
			std::cout << *first << ((++first == last) ? "\n" : delim);
		if (!distance)
			std::cout << std::endl;
	}

	void	put_error(const std::string &str);

	void	*memset(void *b, int c, size_t len);

	unsigned short	host_to_network_short(unsigned short x);

	char    *strdup(const char *s1);

	std::string toUpperStr(const std::string& str);


	struct tm					getTime(time_t sec = 0);

	std::vector<std::string>	get_lines(int fd, size_t max_lines = std::numeric_limits<size_t>::max());
	std::pair<std::string, std::string>	get_keyval(std::string raw, std::string delimiter = ": ");

	size_t	first_of_group(std::string raw, const std::vector<std::string>& delim_groups, size_t search_start, int& match);
	std::vector<std::string>	split(std::string raw, std::vector<std::string>& delim);

	std::vector<std::string>	split(std::string raw, std::string delim, std::string preserve_delim = "");

	struct size_compare
	{
		bool	operator() (const std::string& a, const std::string& b) const;
	};

	bool	isUpperStr(const std::string& str);

	bool	isLowerStr(const std::string& str);

	bool	onlyConsistsOf(const std::string& str, std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	std::string	base64decode(std::string input, std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

	std::string removeSet(std::string str, std::string remove);
}

#endif
