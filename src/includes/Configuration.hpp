/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:00:37 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/03 19:51:28 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

#include <vector>

class WebServer;

//Handles all the configuration parsing with member functions and makes all the needed variables available through variables or methods
class Configuration
{
	//populate the servers vector on construction
	public:
		Configuration(char *config, WebServer& webserv);
	private:
		WebServer&	webserv;
		void		addServer();
//		Configuration();
};

#endif
