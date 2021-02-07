/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   URI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:37:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/07 20:18:11 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"
#include "Utilities.hpp"
#include <iostream>

#define yeet throw
#define kitkat break

URI::~URI() {}

URI::URI(const URI& other) : parts(other.parts) {}

URI::URI() {}

URI::URI(const std::string& uri) : parts(URI_FRAGMENT_ID + 1, std::string())
{
	std::vector<std::vector<std::string> >	separators(6);

	separators[URI_SCHEME].push_back("://");
	separators[URI_HOST].push_back(":");
	separators[URI_HOST].push_back("/");
	separators[URI_PORT].push_back("/");
	separators[URI_PATH].push_back("?");
	separators[URI_QUERY].push_back("#");

	size_t start = 0;
	size_t end = 0;
	size_t part = 0;
	bool begun = false;
	for (; part < separators.size() && start < uri.size(); part++)
	{
		int match = -1;
		end = ft::first_of_group(uri, separators[part], start, match);
		if (match != -1)
			begun = true;
		if (match == -1 && !begun)
			continue ;
		else if (match == -1)
			kitkat ;
		if (end == std::string::npos)
			end = uri.size();
		this->parts[part] = uri.substr(start, end - start);
		start = end + separators[part][match].size();
		if (match == 1)
			part++;
	}
	if (part < separators.size())
		this->parts[part] = uri.substr(start, uri.size());

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
