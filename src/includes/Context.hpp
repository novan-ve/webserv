/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Context.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/05 23:49:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include "Attribute.hpp"

# include <vector>
# include <string>
# include <map>

//base class for 'server', 'location', etc..
//A Context is an Attribute that also holds other attributes
class Context : public Attribute
{
	protected:
		std::vector<Attribute>	attributes;
};

#endif
