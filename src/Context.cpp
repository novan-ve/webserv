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

#include "Attribute.hpp"
#include "Context.hpp"
#include "Properties.hpp"

#include "Location.hpp"
#include "Server.hpp"

Attribute&	Context::attributeSpawner(std::string key)
{
	if (key == "server")
	{
		this->children.push_back(new Server(this->context));
		return (*this->children.back());
	}
	else if (key == "location")
	{
		this->children.push_back(new Location(this->context));
		return (*this->children.back());
	}
	else if (key == "limit_except")
	{
		this->temporaries.push_back(new LimitExcept(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "root")
	{
		this->temporaries.push_back(new Root(this->context));
		return (*this->temporaries.back());
	}
	// else if (key == "allow")
	// {
	// 	this->temporaries.push_back(new Allow(this->context));
	// 	return (*this->temporaries.back());
	// }
	// else if (key == "deny")
	// {
	// 	this->temporaries.push_back(new Deny(this->context));
	// 	return (*this->temporaries.back());
	// }
	else if (key == "client_max_body_size")
	{
		this->temporaries.push_back(new MaxClientBodySize(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "autoindex")
	{
		this->temporaries.push_back(new AutoIndex(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "index")
	{
		this->temporaries.push_back(new Index(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "error_page")
	{
		this->temporaries.push_back(new ErrorPage(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "server_name")
	{
		this->temporaries.push_back(new ServerName(this->context));
		return (*this->temporaries.back());
	}
	else if (key == "listen")
	{
		this->temporaries.push_back(new Listen(this->context));
		return (*this->temporaries.back());
	}
	else
		throw std::runtime_error("Error: unrecognized keyword in config-parser");
}

//Parent Context
Context::Context() : Attribute(*this), parent(*this), properties() {}

//Child Context
Context::Context(Context& parent) : Attribute(parent.context), parent(parent), properties(parent.properties) {}

Context::~Context()
{
	for (size_t i = 0; i < children.size(); i++)
	{
		if (dynamic_cast<Server *>(children[i]))
			delete dynamic_cast<Server*>(children[i]);
		else if (dynamic_cast<Location *>(children[i]))
			delete dynamic_cast<Location*>(children[i]);
		else
			throw std::runtime_error("Error: Unrecognized parser-Context type");
	}
	children.clear();
}
