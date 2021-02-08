/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ReadUtils.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 16:13:27 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/08 16:01:49 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <iostream>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

namespace ft
{
	std::vector <std::string> get_lines(int fd, size_t max_lines = std::numeric_limits<size_t>::max()) {
		static std::map<int, std::string> buffers;
		std::vector <std::string> lines;
		char buf[BUFFER_SIZE + 1];
		ssize_t bytes_read = 1;
		size_t end_pos;

		for (size_t i = 0; i < max_lines && bytes_read; i++) {
			while ((end_pos = buffers[fd].find('\n')) == std::string::npos) //while there is no newline in buffer
			{
				if (buffers[fd].size()) //add the remainder to line
				{
					if (i >= lines.size())
						lines.push_back(buffers[fd]);
					else
						lines[i] += buffers[fd];
				}
				bytes_read = read(fd, buf, BUFFER_SIZE); //read again
				if (bytes_read < 0)
					return (lines);
                else if (bytes_read == 0)
                    break;
				buf[bytes_read] = '\0';
				buffers[fd] = std::string(buf); //replace buffer with newly read data
			}
			end_pos = buffers[fd].find('\n');
			if (end_pos != std::string::npos) //if there is a newline, we add the last part of the line
			{
				std::string new_line = buffers[fd].substr(0, end_pos);
				if (i >= lines.size())
					lines.push_back(new_line);
				else
					lines[i].append(new_line);
			} else
				end_pos = buffers[fd].size() - 1;
			buffers[fd] = buffers[fd].substr(end_pos + 1,
											 buffers[fd].size()); //remove the last part of the line from buff
			if (bytes_read <= 0) //last line, done reading
			{
				buffers.erase(fd);
				break;
			}
		}
		return (lines);
	}

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
}
