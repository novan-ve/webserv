/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Attribute.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 10:06:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 17:16:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"
#include "Attribute.hpp"

//set Context of attribute
Attribute::Attribute(Context& context) : context(context) {}

Attribute&	Attribute::handle_keyword(std::string key)
{
	return (this->context.attributeSpawner(key));
}

void	Attribute::cleanupTemporaries()
{
	for (size_t i = 0; i < temporaries.size(); i++)
		delete temporaries[i];
	temporaries.clear();
}

Attribute::~Attribute() {}

Root::Root(Context& context) : Attribute(context) {}
void	Root::handle_args(std::list<std::string> args)
{
	(void)args;
}

AutoIndex::AutoIndex(Context& context) : Attribute(context) {}
void	AutoIndex::handle_args(std::list<std::string> args)
{
	(void)args;
}

Index::Index(Context& context) : Attribute(context) {}
void	Index::handle_args(std::list<std::string> args)
{
	(void)args;
}

// Deny::Deny(Context& context) : Attribute(context) {}
// void	Deny::handle_args(std::list<std::string> args)
// {
// 	(void)args;
// }

// Allow::Allow(Context& context) : Attribute(context) {}
// void	Allow::handle_args(std::list<std::string> args)
// {
// 	(void)args;
// }

LimitExcept::LimitExcept(Context& context) : Attribute(context)
{
	this->keywords.push_back("allow");
	this->keywords.push_back("deny");
}
void	LimitExcept::handle_args(std::list<std::string> args)
{
	(void)args;
}

MaxClientBodySize::MaxClientBodySize(Context& context) : Attribute(context) {}
void	MaxClientBodySize::handle_args(std::list<std::string> args)
{
	(void)args;
}

ErrorPage::ErrorPage(Context& context) : Attribute(context) {}
void	ErrorPage::handle_args(std::list<std::string> args)
{
	(void)args;
}

ServerName::ServerName(Context& context) : Attribute(context) {}
void	ServerName::handle_args(std::list<std::string> args)
{
	(void)args;
}

Listen::Listen(Context& context) : Attribute(context) {}
void	Listen::handle_args(std::list<std::string> args)
{
	(void)args;
}
