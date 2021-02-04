/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   URI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:37:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 20:30:22 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"
#include <iostream>

URI::~URI() {}

URI::URI(const URI& other) : parts(other.parts) {}

URI::URI() {}

URI::URI(const std::string& uri) : parts(URI_FRAGMENT_ID + 1, std::string())
{
	const char *sep[] = {
		"://",
		":",
		"/",
		"?",
		"#",
		""
	};
	std::vector<std::string>	separators(sep, sep + (sizeof(sep) / sizeof(char *)));

	size_t start = 0;
	size_t end = 0;
	for (size_t part = 0; part < separators.size() && end < uri.size(); part++)
	{
		size_t	current_part = part;
		end = uri.find_first_of(separators[current_part], start);
		for (;end == std::string::npos && part + 1 < separators.size(); part++)
			end = uri.find_first_of(separators[part + 1], start);
		end = (end == std::string::npos) ? uri.size() : end;
		this->parts[current_part] = uri.substr(start, end - start);
		start = end + separators[current_part].size();
	}

	// const char *partnames[] = {
	// 	"SCHEME",
	// 	"HOST",
	// 	"PORT",
	// 	"PATH",
	// 	"QUERY",
	// 	"FRAGMENT"
	// };

	// for (size_t i = 0; i < parts.size(); i++)
	// 	std::cout << partnames[i] << " = " << parts[i] << std::endl;
}
