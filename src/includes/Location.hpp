/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Location.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 01:10:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 18:46:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <list>
# include <string>

# include "Utilities.hpp"
# include "Context.hpp"
# include "Attribute.hpp"

class Location : public Context
{
	public:
//		Location();
		~Location();
		Location(Context& parent);
		Location(const Location& other);
		void		handle_args(std::list<std::string> args);
};

#endif
