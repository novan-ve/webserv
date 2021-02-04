/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utilities.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 21:38:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 21:46:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include <map>

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

	void	put_error(const std::string &str);

	void	*memset(void *b, int c, size_t len);

	unsigned short	htons(unsigned short x);
}

#endif
