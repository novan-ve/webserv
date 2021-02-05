/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:29:21 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/05 15:59:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>

namespace ft
{
	size_t	first_of_group(std::string raw, const std::vector<std::string>& delim_groups, size_t search_start, int& group)
	{
		size_t smallest = std::string::npos;

		for (size_t i = 0; i < delim_groups.size(); i++)
		{
			size_t tmp = raw.find_first_of(delim_groups[i], search_start);
			if (tmp < smallest)
			{
				group = i;
				smallest = tmp;
			}
		}
		return (smallest);
	}

	std::vector<std::string>	split(std::string raw, std::vector<std::string>	delim_groups, bool preserve_delim = false)
	{
		std::vector<std::string>	tokens;
		size_t	end;
		int last_group = -1;
		for (size_t begin = 0 ; begin < raw.size();)
		{
			end = first_of_group(raw, delim_groups, begin, last_group);
			std::cout << end << " char: " << ((end != std::string::npos) ? std::string(1, raw[end]) : std::string(" END")) << std::endl;
			if (end == std::string::npos)
				end = raw.size();
			if (begin != end)
				tokens.push_back(raw.substr(begin, end - begin));
			if (preserve_delim && end < raw.size())
			{
				tokens.push_back(std::string(1, raw[end++]));
				for (; end < raw.size() && last_group != -1 && delim_groups[last_group].find(raw[end]) != std::string::npos; end++) {}
			}
			else
			{
				for (; end != raw.size() && last_group != -1; end++)
				{
					bool is_delim = false;
					for (size_t i = 0; i < delim_groups.size() && !is_delim; i++)
						is_delim = (delim_groups[i].find(raw[end]) != std::string::npos);
					if (!is_delim)
						break ;
				}
			}
			begin = end;
		}
		for (size_t i = 0; i < tokens.size(); i++)
		{
			std::cout << "'" << ((tokens[i] == "\n") ? "\\n" : tokens[i]) << "'" << std::endl;
		}
		return (tokens);
	}

	void	put_error(const std::string &str) {

		std::cout << "Webserv: " << str << std::endl;
		exit(EXIT_FAILURE);
	}

	void	*memset(void *b, int c, size_t len)
	{
		unsigned char	*str;

		str = static_cast<unsigned char*>(b);
		while (len > 0)
		{
			*str = c;
			str++;
			len--;
		}
		return (b);
	}

	unsigned short	htons(unsigned short x)
	{
		return ((((x) >> 8) & 0xff ) | (((x) & 0xff) << 8));
	}
}
