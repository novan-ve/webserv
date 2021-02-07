/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Attribute.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 10:06:11 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 23:18:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"
#include "Attribute.hpp"
#include "Utilities.hpp"

//set Context of attribute
Attribute::Attribute(Context& context) : context(context)
{
	std::cout << "ATTRIBUTE CONSTRUCTOR!!!!!" << std::endl;
}

Attribute&	Attribute::handle_keyword(std::string key)
{
	return (this->context.attributeSpawner(key));
}

Attribute::~Attribute()
{
	std::cout << "ATTRIBUTE DESTRUCTOR OF " << this->type << "!!!!!" << std::endl;
	for (size_t i = 0; i < this->temporaries.size(); i++)
		delete temporaries[i];
	temporaries.clear();
}

Root::Root(Context& context) : Attribute(context) { this->type = "Root"; }
void	Root::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "Root ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

AutoIndex::AutoIndex(Context& context) : Attribute(context) { this->type = "AutoIndex"; }
void	AutoIndex::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "AutoIndex ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

Index::Index(Context& context) : Attribute(context) { this->type = "Index"; }
void	Index::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "Index ARGS: ";
	ft::print_iteration(args.begin(), args.end());
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
	this->type = "LimitExcept";
	// this->keywords.push_back("allow");
	// this->keywords.push_back("deny");
}
void	LimitExcept::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "LimitExcept ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

MaxClientBodySize::MaxClientBodySize(Context& context) : Attribute(context) { this->type = "MaxClientBodySize"; }
void	MaxClientBodySize::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "MaxClientBodySize ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

ErrorPage::ErrorPage(Context& context) : Attribute(context) { this->type = "ErrorPage"; }
void	ErrorPage::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "ErrorPage ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

ServerName::ServerName(Context& context) : Attribute(context) { this->type = "ServerName"; }
void	ServerName::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "ServerName ARGS: ";
	ft::print_iteration(args.begin(), args.end());
}

Listen::Listen(Context& context) : Attribute(context) { this->type = "Listen"; }
void	Listen::handle_args(std::list<std::string> args)
{
	(void)args;
	std::cout << "Listen ARGS: ";
	ft::print_iteration(args.begin(), args.end());
	if (args.size() != 1 && args.size() != 2)
		throw std::runtime_error("Error: incorrect amount of arguments to 'listen'");
}
Listen::~Listen()
{
	std::cout << "LISTEN DECONSTRUCTED" << std::endl;
}
