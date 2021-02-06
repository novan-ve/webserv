/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Scope.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 09:31:26 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_HPP
# define SCOPE_HPP

# include "Attribute.hpp"
# include "Properties.hpp"

# include <vector>
# include <string>
# include <map>

//base class for 'server', 'location', etc..
//A scope is an Attribute that holds properties

class Scope : public Attribute
{
	public:
		Scope();
		Scope(Scope& other);
		virtual ~Scope();
	protected:
		Scope&	parent;
		Properties	properties;
};

#endif
