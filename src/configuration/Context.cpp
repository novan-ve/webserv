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
	WebServer& parent = dynamic_cast<WebServer&>(*this);
	parent.servers[elem->_server_fd] = elem;
	FD_SET(elem->_server_fd, &parent.sockets);
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
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	// else if (args.size() == 1)
	// {
	// 	std::vector<std::string>	host_port = ft::split(args.back(), ":");
	// 	if (host_port.size() == 2)


	// }
	return (NULL);
}

Context *Context::key_server_name(const std::list<std::string>& args)
{
	std::cout << "SERVER_NAME" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_client_max_body_size(const std::list<std::string>& args)
{
	std::cout << "MAX_CLIENT_BODY_SIZE" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_autoindex(const std::list<std::string>& args)
{
	std::cout << "AUTOINDEX" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_index(const std::list<std::string>& args)
{
	std::cout << "INDEX" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_error_page(const std::list<std::string>& args)
{
	std::cout << "ERROR_PAGE" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_limit_except(const std::list<std::string>& args)
{
	std::cout << "LIMIT_EXCEPT" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
	return (NULL);
}

Context *Context::key_root(const std::list<std::string>& args)
{
	std::cout << "ROOT" << std::endl;
	if (!args.size())
		throw ft::runtime_error("Error: No arguments given to 'listen'");
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
