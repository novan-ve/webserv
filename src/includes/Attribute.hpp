/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Attribute.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 17:15:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATTRIBUTE_HPP
# define ATTRIBUTE_HPP

# include <vector>
# include <string>
# include <map>
# include <list>
# include <stdexcept>

//# include "Context.hpp"

//KEYWORD [ARGS] { [KEYWORD] }

class Context;

class Attribute
{
	public:
		virtual void		handle_args(std::list<std::string> args) = 0;
		virtual Attribute& 	handle_keyword(std::string key);

		void				cleanupTemporaries();
		Attribute();
		Attribute(Context& context);
		virtual ~Attribute();
		//keywords that the attribute responds to for parsing
		std::vector<std::string>	keywords;
		Context&					context;
		std::vector<Attribute*>		temporaries;
};

//----------------------------------------ATTRIBUTES---------------------------------------------
//To add a new attribute, create a new Class down here
//Implement its constructor and its handle_args() accordingly in the Attribute.cpp file
//Add it to Context::attributeSpawner
//Add its keyword to the 'keywords' of the attribute(s) it's a part of

class Root : public Attribute
{
	public:
		Root(Context& context);
		void	handle_args(std::list<std::string> args);
};

class MaxClientBodySize : public Attribute
{
	public:
		MaxClientBodySize(Context& context);
		void	handle_args(std::list<std::string> args);
};

class AutoIndex : public Attribute
{
	public:
		AutoIndex(Context& context);
		void	handle_args(std::list<std::string> args);
};

class Index : public Attribute
{
	public:
		Index(Context& context);
		void	handle_args(std::list<std::string> args);
};

// class Allow : public Attribute
// {
// 	public:
// 		Allow(Context& context);
// 		void	handle_args(std::list<std::string> args);
// };

// class Deny : public Attribute
// {
// 	public:
// 		Deny(Context& context);
// 		void	handle_args(std::list<std::string> args);
// };

class LimitExcept : public Attribute
{
	public:
		LimitExcept(Context& context);
		void	handle_args(std::list<std::string> args);
};

class ServerName : public Attribute
{
	public:
		ServerName(Context& context);
		void	handle_args(std::list<std::string> args);
};

class ErrorPage : public Attribute
{
	public:
		ErrorPage(Context& context);
		void	handle_args(std::list<std::string> args);
};

class Listen : public Attribute
{
	public:
		Listen(Context& context);
		void	handle_args(std::list<std::string> args);
};

#endif
