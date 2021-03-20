/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:00:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/07 16:50:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

#include <vector>
#include <list>
#include <string>

# include "Parse.hpp"

class WebServer;

//Handles all the configuration parsing with member functions and makes all the needed variables available through variables or methods
class Configuration
{
	public:
		Configuration(char *config, WebServer* webserv);
		Configuration(const Configuration & src);
		Configuration&	operator=(const Configuration & rhs);
		virtual ~Configuration();
		void	parse();
	private:
		int		fd;
		void	populateTokens(std::list<std::string>& tokens);
		WebServer*	webserv;
		Configuration();
};

#endif
