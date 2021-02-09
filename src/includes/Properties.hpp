/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Properties.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 09:28:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 09:37:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTIES_HPP
# define PROPERTIES_HPP

# include <map>
# include <vector>
# include <list>
# include <string>
# include <iostream>

struct Properties
{
	Properties();
	Properties(const Properties& other);

	std::map<std::string, size_t>	values;
};

#endif
