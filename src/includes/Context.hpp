/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Context.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 16:55:03 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include "Attribute.hpp"
# include "Properties.hpp"

# include <vector>
# include <string>
# include <map>

//base class for 'server', 'location', etc..
//A Context is an Attribute that holds properties

class Context : public Attribute
{
	public:
		Context();
		Context(Context& other);
		virtual ~Context();
		Attribute&	attributeSpawner(std::string key);
	protected:
		Context&				parent;
		Properties			properties;
		std::vector<Context*>	children;
		std::vector<Attribute*>	temporaries;
};

#endif
