/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   URI.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:37:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/11 16:21:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "URI.hpp"
#include "Utilities.hpp"
#include <iostream>

#define yeet throw
#define kitkat break

URI::~URI() {}

URI::URI(const URI& other) : str(other.str), parts(other.parts) {}

URI::URI() {}

void	URI::print_state()
{
	const char *partnames[] = {
		"SCHEME",
		"HOST",
		"PORT",
		"PATH",
		"QUERY",
		"FRAGMENT"
	};

	for (size_t i = 0; i < this->parts.size(); i++)
		std::cout << partnames[i] << " = " << this->parts[i] << std::endl;
}

URI::URI(const std::string& uri)
{
	set_uri(uri);
	//print_state();
}

URI::PartModifier::PartModifier(URI& uri, std::string &str, e_uri id) : uri(uri), id(id), str(str) {}

void	URI::PartModifier::operator () (std::string updated)
{
	this->str = updated;
	if (this->id == URI_FULL)
		this->uri.set_uri(updated);
	else
		this->uri.set_parts(this->uri.parts);
}

const std::string& URI::operator [] (e_uri id)
{
	return (this->parts[id]);
}

URI::PartModifier URI::operator [] (std::string part)
{
	if (part == "scheme")
		return PartModifier(*this, this->parts[URI_SCHEME], URI_SCHEME);
	else if (part == "host")
		return PartModifier(*this, this->parts[URI_HOST], URI_HOST);
	else if (part == "port")
		return PartModifier(*this, this->parts[URI_PORT], URI_PORT);
	else if (part == "path")
		return PartModifier(*this, this->parts[URI_PATH], URI_PATH);
	else if (part == "query")
		return PartModifier(*this, this->parts[URI_QUERY], URI_QUERY);
	else if (part == "fragment")
		return PartModifier(*this, this->parts[URI_FRAGMENT_ID], URI_FRAGMENT_ID);
	else
		return PartModifier(*this, this->str, URI_FULL);
}

//----------------------------------------------------

const std::string&	URI::get_uri()
{
	return (this->str);
}

const std::string&	URI::get_scheme()
{
	return (this->parts[URI_SCHEME]);
}

const std::string&	URI::get_host()
{
	return (this->parts[URI_HOST]);
}

const std::string&	URI::get_port()
{
	return (this->parts[URI_PORT]);
}

const std::string&	URI::get_path()
{
	return (this->parts[URI_PATH]);
}

const std::string&	URI::get_query()
{
	return (this->parts[URI_QUERY]);
}

const std::string&	URI::get_fragment()
{
	return (this->parts[URI_FRAGMENT_ID]);
}

std::vector<std::string>	URI::get_parts()
{
	return (this->parts);
}

//----------------------------------------------------

void	URI::set_scheme(std::string updated)
{
	this->parts[URI_SCHEME] = updated;
	this->set_parts(this->parts);
}

void	URI::set_host(std::string updated)
{
	this->parts[URI_HOST] = updated;
	this->set_parts(this->parts);
}

void	URI::set_port(std::string updated)
{
	this->parts[URI_PORT] = updated;
	this->set_parts(this->parts);
}

void	URI::set_path(std::string updated)
{
	this->parts[URI_PATH] = updated;
	this->set_parts(this->parts);
}

void	URI::set_query(std::string updated)
{
	this->parts[URI_QUERY] = updated;
	this->set_parts(this->parts);
}

void	URI::set_fragment(std::string updated)
{
	this->parts[URI_FRAGMENT_ID] = updated;
	this->set_parts(this->parts);
}

void	URI::set_parts(const std::vector<std::string>& updated)
{
	if (parts.size() != 6)
		return ;

	const char *sep[] = {
		"://",
		":",
		"/",
		"?",
		"#",
		""
	};
	std::vector<std::string>	separators(sep, sep + (sizeof(sep) / sizeof(char *)));

	this->parts = updated;
	this->str.clear();
	for (size_t i = 0 ; i < parts.size(); i++)
	{
		if (i && parts[i].size())
			this->str += sep[i - 1];
		this->str += parts[i];
	}
}

void	URI::set_uri(std::string uri)
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
	ssize_t nextpart;
	bool begun = false;
	this->str = uri;
	this->parts = std::vector<std::string>(6, std::string());
	for (; part < separators.size() && start < uri.size(); part++)
	{
		nextpart = -1;
		int match = -1;
		end = ft::first_of_group(uri, separators[part], start, match);
		if (match != -1)
			begun = true;
		if (match == -1 && !begun)
			continue ;
		else if (match == -1)
		{
			nextpart = part + 1;
			for (; nextpart < separators.size(); nextpart++)
			{
				end = ft::first_of_group(uri, separators[nextpart], start, match);
				if (match != -1)
					break ;
			}
			//no separator was found
			if (nextpart == separators.size())
				break ;
		}
		if (end == std::string::npos)
			end = uri.size();
		this->parts[part] = uri.substr(start, end - start);
		start = end + separators[part][match].size();
		if (nextpart != -1)
			part = nextpart;
		if (match == 1)
			part++;
	}
	if (part < separators.size())
		this->parts[part] = uri.substr(start, uri.size());
//	this->print_state();
}
