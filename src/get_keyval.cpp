/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_keyval.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 15:24:13 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 15:28:40 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <algorithm>
#include <iostream>
#include <utility>

std::pair<std::string, std::string>	get_keyval(std::string raw, char delimiter = ':')
{
	std::pair<std::string, std::string>	keyval;
	size_t	delim_pos = raw.find(delimiter);
	if (delim_pos == std::string::npos)
		return (keyval);
	keyval.first = raw.substr(0, delim_pos);
	keyval.second = raw.substr(delim_pos + 2, raw.size());
	return (keyval);
}
