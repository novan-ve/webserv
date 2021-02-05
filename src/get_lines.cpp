/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_lines.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 13:00:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/05 13:27:25 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <iostream>

namespace ft
{
	std::vector<std::string>	get_lines(int fd, size_t max_lines = std::numeric_limits<size_t>::max())
	{
		static std::map<int,std::string>	buffers;
		std::vector<std::string>			lines;
		char								buf[BUFFER_SIZE + 1];
		size_t								bytes_read = 1;
		size_t								end_pos;

		for (size_t i = 0; i < max_lines && bytes_read; i++)
		{
			while (end_pos = buffers[fd].find('\n') == std::string::npos) //while there is no newline in buffer
			{
				if (buffers[fd].size()) //add the remainder to line
				{
					if (i >= lines.size())
						lines.push_back(buffers[fd]);
					else
						lines[i] += buffers[fd];
				}
				bytes_read = read(fd, buf, BUFFER_SIZE); //read again
				buf[bytes_read] = '\0';
				buffers[fd] = std::string(buf); //replace buffer with newly read data
				if (!bytes_read)
					break ;
			}
			end_pos = buffers[fd].find('\n');
			if (end_pos != std::string::npos) //if there is a newline, we add the last part of the line
			{
				std::string new_line = buffers[fd].substr(0, end_pos);
				if (i >= lines.size())
					lines.push_back(new_line);
				else
					lines[i].append(new_line);
			}
			else
				end_pos = buffers[fd].size() - 1;
			buffers[fd] = buffers[fd].substr(end_pos + 1, buffers[fd].size()); //remove the last part of the line from buff
			if (!bytes_read) //last line, done reading
			{
				buffers.erase(fd);
				break ;
			}
		}
		return (lines);
	}
}
