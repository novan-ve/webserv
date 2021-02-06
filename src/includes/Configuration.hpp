/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:00:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 01:10:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

#include <vector>
#include <list>
#include <string>

# include "Attribute.hpp"
# include "Context.hpp"
# include "Parse.hpp"

class WebServer;

//Handles all the configuration parsing with member functions and makes all the needed variables available through variables or methods
class Configuration
{
	public:
		Configuration(char *config, WebServer& webserv);
		~Configuration();
		void	parse();
	private:
		int		fd;
		void	populateTokens(std::list<std::string>& tokens);
		WebServer&	webserv;
		void		addServer();
//		Configuration();
};

class Root : public Attribute
{
	public:
		void	handle_args(std::list<std::string> args);
};

class LimitExcept : public Context
{
	public:
		void	handle_args(std::list<std::string> args);

};

#endif
