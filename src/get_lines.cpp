/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_lines.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 13:00:05 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/03 11:13:40 by tishj         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>
#include <iostream>

#include "Utilities.hpp"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

namespace ft
{
	std::vector<std::string>	get_lines(int fd, std::string eol_sequence, int* ret, bool encoding, size_t max_lines)
	{
		static std::map<int,std::string>	buffers;
		std::vector<std::string>			lines;
		char								buf[BUFFER_SIZE + 1];
		ssize_t								bytes_read = 1;
		size_t								end_pos;

		for (size_t i = 0; i < max_lines && bytes_read; i++)
		{
//			std::cout << "GET_LINES BUFFER[" << fd << "] = " << buffers[fd] << "\n" << std::endl;
			while ((end_pos = buffers[fd].find(eol_sequence)) == std::string::npos) //while there is no newline in buffer
			{
		//		std::cerr << "\nNO EOL_SEQUENCE FOUND\n";
				bytes_read = read(fd, buf, BUFFER_SIZE); //read again
				if (bytes_read == -1)
				{
					if (buffers[fd] != "\r" && buffers[fd].size() && !encoding && std::find(lines.begin(), lines.end(), "") != lines.end())
					{
						end_pos = buffers[fd].find(eol_sequence);
						lines.push_back(buffers[fd].substr(0, end_pos));
						buffers.erase(fd);
					}
//					buffers.erase(fd);
					return (lines);
				}
				buf[bytes_read] = '\0';
				buffers[fd] += std::string(buf); //replace buffer with newly read data
				if (!bytes_read)
				{
					if (ret && !lines.size())
						*ret = -1;
					break ;
				}
			}
			end_pos = buffers[fd].find(eol_sequence);
			if (end_pos != std::string::npos) //if there is a newline, we add the last part of the line
			{
				std::string new_line;
				if (end_pos == buffers[fd].size())
					new_line = "";
				else
					new_line = buffers[fd].substr(0, end_pos);
		//		std::cerr << "NEW_LINE: " << new_line << std::endl;
				if (new_line.empty())
					lines.push_back("");
				else if (i >= lines.size())
					lines.push_back(new_line);
				else
					lines[i].append(new_line);
				buffers[fd] = buffers[fd].substr(end_pos + eol_sequence.size(), buffers[fd].size()); //remove the last part of the line from buff
			}
			else
			{
				end_pos = buffers[fd].size() - 1;
				buffers[fd].clear();
			}
			if (bytes_read == 0) //last line, done reading
				return (lines);
			if (bytes_read == -1)
			{
				buffers[fd].clear();
				return (lines);
			}
		}
		return (lines);
	}
}
