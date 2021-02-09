/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/01 20:29:21 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/09 19:12:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <map>
#include <sys/time.h>
#include <vector>
#include <string>
#include <algorithm>

namespace ft
{
	std::string	itos(int num, const std::string base = "0123456789")
	{
		size_t size = 0;
		for (int tmp = num; tmp ; tmp /= base.size(), size++) {}

		std::string	number(size, '\0');
		for (--size ; num ; num /= base.size(), size--)
			number[size] = base[num % base.size()];
		return (number);
	}

	int stoi(std::string number, const std::string base = "0123456789")
	{
		int res = 0;

		for (size_t i = 0; i < number.size(); i++)
		{
			size_t num = base.find(number[i]);
			if (num == std::string::npos)
				throw std::runtime_error("Error: string is not a number");
			res = res * 10 + num;
		}
		return (res);
	}

	size_t	first_of_group(std::string raw, const std::vector<std::string>& delim_groups, size_t search_start, int& match)
	{
		size_t smallest = std::string::npos;

		for (size_t i = 0; i < delim_groups.size(); i++)
		{
			size_t tmp = raw.find(delim_groups[i], search_start);
			if (tmp < smallest)
			{
				match = (int)i;
				smallest = tmp;
			}
		}
		return (smallest);
	}

	std::vector<std::string>	split(std::string raw, std::vector<std::string>& delim)
	{
		std::vector<std::string>	tokens;
		size_t	end;
		int		match;
		for (size_t begin = 0 ; begin < raw.size();)
		{
			match = -1;
			end = first_of_group(raw, delim, begin, match);
			if (end == std::string::npos)
				end = raw.size();
			if (begin != end)
				tokens.push_back(raw.substr(begin, end - begin));
			if (match == -1)
				break ;
			begin = end + delim[match].size();
		}
		return (tokens);
	}

	std::vector<std::string>	split(std::string raw, std::string delim, std::string preserve_delim = "")
	{
		std::vector<std::string>	tokens;
		size_t	end;
		for (size_t begin = 0 ; begin < raw.size();)
		{
			end = raw.find_first_of(delim, begin);
			if (end == std::string::npos)
				end = raw.size();
			if (begin != end)
				tokens.push_back(raw.substr(begin, end - begin));
			if (preserve_delim.size() && end < raw.size() && preserve_delim.find(raw[end]) != std::string::npos)
				tokens.push_back(std::string(1, raw[end]));
			for (end = end + 1; end < raw.size() && delim.find(raw[end]) != std::string::npos && (preserve_delim.size() == 0 || preserve_delim.find(raw[end]) == std::string::npos) ; end++) {}
			begin = end;
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

	std::string getTime(void) {

		struct timeval	tv;
		struct tm		tm;
		char 			buf[64];

		ft::memset(buf, '\0', 64);

		gettimeofday(&tv, NULL);

		tm.tm_sec = tv.tv_sec % 60;

		int minutes = (tv.tv_sec - tm.tm_sec) / 60;

		tm.tm_min =  minutes % 60;
		int days = (((minutes - tm.tm_min) / 60) + 1) / 24;
		int year = ((((minutes - tm.tm_min) / 60) + 1) / 24) / 365 + 1970;

		tm.tm_year = year - 1900;
		tm.tm_hour = (((minutes - tm.tm_min) / 60) + 1) % 24;
		tm.tm_yday = (days % 365 - ((year - 1972) / 4)) - 1;

		int	monthdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		// Change february if leap year
		if ((year - 1972) % 4 == 0)
			monthdays[1] = 29;

		// Check if daylight saving time is active
		int		first_day;
		int 	last_day = 0;

		first_day = monthdays[0] + monthdays[1] + monthdays[2] - 1;
		while ((tm.tm_year * 365 + first_day + ((year - 1900) / 4)) % 7 != 6)
			first_day--;

		for (int i = 0; i < 10; i++)
			last_day += monthdays[i];
		while ((tm.tm_year * 365 + last_day + ((year - 1900) / 4)) % 7 != 6)
			last_day--;

		// If time is between last sunday of march and last sunday of october, add hour for daylight saving time
		if ((tm.tm_yday > first_day || (tm.tm_yday == first_day && tm.tm_hour >= 2)) &&
			(tm.tm_yday < last_day || (tm.tm_yday == last_day && tm.tm_hour <= 2))) {
			tv.tv_sec += 3600;
		}

		tm.tm_sec = tv.tv_sec % 60;
		minutes = (tv.tv_sec - tm.tm_sec) / 60;
		tm.tm_min =  minutes % 60;

		int hours = ((minutes - tm.tm_min) / 60) + 1;

		tm.tm_hour = hours % 24;
		days = hours / 24;
		year = days / 365 + 1970;
		tm.tm_year = year - 1900;
		tm.tm_mday = days % 365 - ((year - 1972) / 4);
		tm.tm_yday = tm.tm_mday;

		// Set correct month
		for (int i = 0; i < 12; i++) {
			// Found month
			if (tm.tm_mday < monthdays[i] + 1 ) {
				tm.tm_mon = i;
				break;
			}
			tm.tm_mday -= monthdays[i];
		}

		// Set correct weekday
		tm.tm_wday = (tm.tm_year * 365 + tm.tm_yday + ((year - 1900) / 4)) % 7;

		strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm);

		return std::string(buf);
	}
}
