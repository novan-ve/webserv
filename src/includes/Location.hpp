/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:10:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 01:25:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <list>
# include <string>

# include "Context.hpp"
# include "Utilities.hpp"

class Location : public Context
{
	public:
		Location();
		Location(const Location& other);
		void		handle_args(std::list<std::string> args);
};

#endif
