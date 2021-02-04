/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ReadUtils.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 16:11:06 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/04 16:11:07 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef READUTILS_HPP
# define READUTILS_HPP

# include <vector>
# include <limits>

namespace ft
{
	std::vector <std::string> get_lines(int fd, size_t max_lines = std::numeric_limits<size_t>::max());

	std::pair<std::string, std::string>	get_keyval(std::string raw, char delimiter = ':');
}

#endif
