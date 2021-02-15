/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Context.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 09:33:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 16:23:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"
#include "Properties.hpp"
#include <utility>
#include <list>
#include <string>
#include <vector>
#include <map>

#include "Location.hpp"
#include "Server.hpp"
#include "WebServer.hpp"

//Parent Context
Context::Context() : parent(*this), properties() {}

//Child Context
Context::Context(Context& parent) : parent(parent), properties(parent.properties) {}

Context *Context::key_server(const std::list<std::string>& args)
{
	std::cout << "CREATE_SERVER CALLED" << std::endl;
	if (args.size())
		throw ft::runtime_error("Error: Arguments provided to 'server'");
	Server *elem = new Server(*this);
	this->children.push_back(elem);
	return (elem);
}

Context	*Context::key_location(const std::list<std::string>& args)
{
	std::cout << "CREATE_LOCATION CALLED" << std::endl;
	if (args.size() != 1)
		throw ft::runtime_error("Error: Not the right amount of arguments given to 'location'");
	Location *elem = new Location(*this);
	Server& parent = dynamic_cast<Server&>(*this);
	parent.locations[args.back()] = elem;
	this->children.push_back(elem);
	return (elem);
}

Context *Context::key_listen(const std::list<std::string>& args)
{
	std::cout << "LISTEN" << std::endl;
	if (args.size() != 1)
		throw ft::runtime_error("Error: Invalid amount of arguments given to 'listen'");
	std::string ip_port = args.front();
	if (ip_port.find(':') != std::string::npos)
	{
		std::pair<std::string, std::string>	keyval = ft::get_keyval(ip_port, ":");
		for (size_t i = 0; i < keyval.second.size(); i++)
			if (keyval.second[i] < '0' || keyval.second[i] > '9')
				throw ft::runtime_error("Error: Invalid port given to 'listen'");
		this->properties.ip_port = keyval;
	}
	else
	{
		bool port = true;
		for (size_t i = 0; i < ip_port.size() && port; i++)
			if (ip_port[i] < '0' || ip_port[i] > '9')
				port = false;
		if (port)
			this->properties.ip_port.second = ip_port;
		else
			this->properties.ip_port.first = ip_port;
	}
	return (NULL);
}

Context *Context::key_server_name(const std::list<std::string>& args)
{
	std::cout << "SERVER_NAME" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'server_name'");
	for (std::list<std::string>::const_iterator it = args.begin(); it != args.end(); it++)
		this->properties.server_names.push_back(*it);
	return (NULL);
}

Context *Context::key_client_max_body_size(const std::list<std::string>& args)
{
	std::cout << "MAX_CLIENT_BODY_SIZE" << std::endl;
	if (args.size() != 1)
		throw ft::runtime_error("Error: Invalid amount of arguments given to 'client_max_body_size'");
	std::string value = args.front();
	for (size_t i = 0; i < value.size(); i++)
	{
		if (!isalnum(value[i]))
			throw std::runtime_error("Error: Invalid value provided to 'client_max_body_size'");
		value[i] = tolower(value[i]);
	}
	std::vector<std::string>	split_value = ft::split(value, "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz");
	if (split_value.size() > 2)
		throw ft::runtime_error("Error: invalid value provided to 'client_max_body_size'");
	if ((split_value[0][0] < '0' || split_value[0][0] > '9') || split_value[1].size() != 1)
		throw ft::runtime_error("Error: invalid value provided to 'client_max_body_size'");
	size_t body_size = ft::stoul(split_value[0]);
	
	if (split_value.size() == 2)
	{
		switch(split_value[1][0])
		{
			case 'k':
				body_size *= 1000; break ;
			case 'm':
				body_size *= 1000000; break ;
			default:
				throw ft::runtime_error("Error: invalid value provided to 'client_max_body_size'");
		}
	}
	this->properties.client_max_body_size = body_size;
	return (NULL);
}

Context *Context::key_autoindex(const std::list<std::string>& args)
{
	std::cout << "AUTOINDEX" << std::endl;
	if (args.size() != 1)
		throw ft::runtime_error("Error: No arguments given to 'autoindex'");
	std::string value = args.front();
	if (value != "off" && value != "on")
		throw ft::runtime_error("Error: Invalid value provided to 'autoindex");
	this->properties.auto_index = (value == "on");
	return (NULL);
}

//might want to add a check to see if it's a valid path..
Context *Context::key_index(const std::list<std::string>& args)
{
	std::cout << "INDEX" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'index'");
	for (std::list<std::string>::const_iterator it = args.begin(); it != args.end(); it++)
		this->properties.index.push_back(*it);
	return (NULL);
}

Context *Context::key_error_page(const std::list<std::string>& args)
{
	std::cout << "ERROR_PAGE" << std::endl;
	if (args.size() < 2)
		throw ft::runtime_error("Error: No arguments given to 'error_page'");
	std::list<std::string>::const_iterator end_of_statuscodes = args.end();
	--end_of_statuscodes;
	std::vector<int>	status_codes;
	std::list<std::string>::const_iterator it = args.begin();
	for (; it != end_of_statuscodes; it++)
		status_codes.push_back(ft::stoi(*it));
	for (size_t i = 0; i < status_codes.size(); i++)
		this->properties.error_pages[status_codes[i]] = *it;
	return (NULL);
}

Context *Context::key_limit_except(const std::list<std::string>& args)
{
	std::cout << "LIMIT_EXCEPT" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'limit_except'");
	for (std::map<std::string, bool>::iterator it = this->properties.accepted_methods.begin(); it != this->properties.accepted_methods.end(); it++)
		it->second = false;
	for (std::list<std::string>::const_iterator it = args.begin(); it != args.end(); it++)
		this->properties.accepted_methods[Method(*it).str] = true;
	return (NULL);
}

//Might want to make sure that it's actually a path
Context *Context::key_root(const std::list<std::string>& args)
{
	std::cout << "ROOT" << std::endl;
	if (args.size() != 1)
		throw ft::runtime_error("Error: No arguments given to 'root'");
	this->properties.root = args.front();
	return (NULL);
}

Context	*Context::parse_keyword(std::string key, std::list<std::string> args)
{
	const static std::pair<std::string, Context::keyword_func>	pairs[] = {
		std::pair<std::string, Context::keyword_func>("server", &Context::key_server),
		std::pair<std::string, Context::keyword_func>("listen", &Context::key_listen),
		std::pair<std::string, Context::keyword_func>("location", &Context::key_location),
		std::pair<std::string, Context::keyword_func>("server_name", &Context::key_server_name),
		std::pair<std::string, Context::keyword_func>("client_max_body_size", &Context::key_client_max_body_size),
		std::pair<std::string, Context::keyword_func>("autoindex", &Context::key_autoindex),
		std::pair<std::string, Context::keyword_func>("index", &Context::key_index),
		std::pair<std::string, Context::keyword_func>("limit_except", &Context::key_limit_except),
		std::pair<std::string, Context::keyword_func>("root", &Context::key_root),
		std::pair<std::string, Context::keyword_func>("error_page", &Context::key_error_page),
	};
	static std::map<std::string, Context::keyword_func>	functions(pairs, pairs + (sizeof(pairs) / sizeof(std::pair<std::string, Context::keyword_func>)));

	if (!functions.count(key))
		throw ft::runtime_error("Error: unrecognized keyword in config-parser");
	return ((this->*(functions[key]))(args));
}

Context::~Context()
{
	std::cout << "CONTEXT DECONSTRUCTOR!!!" << std::endl;
	for (size_t i = 0; i < children.size(); i++)
	{
		if (dynamic_cast<Server *>(children[i]))
			delete dynamic_cast<Server*>(children[i]);
		else if (dynamic_cast<Location *>(children[i]))
			delete dynamic_cast<Location*>(children[i]);
		else
			throw ft::runtime_error("Error: Unrecognized parser-Context type");
	}
	children.clear();
}
