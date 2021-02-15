/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Properties.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 09:28:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/15 15:27:22 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTIES_HPP
# define PROPERTIES_HPP

# include <map>
# include <vector>
# include <list>
# include <string>
# include <iostream>
# include <utility> //illegal

struct Properties
{
	Properties();
	Properties(const Properties& other);
	Properties& operator = (const Properties& other);
	~Properties();

	std::string							root;
	std::pair<std::string, std::string>	ip_port;
	std::vector<std::string>			server_names;
	std::vector<std::string>			index;
	bool								auto_index;
	std::map<std::string, bool>			accepted_methods;
	std::map<int, std::string>			error_pages;
	size_t								client_max_body_size;
};

#endif
