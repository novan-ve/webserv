/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Attribute.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 01:21:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATTRIBUTE_HPP
# define ATTRIBUTE_HPP

# include <vector>
# include <string>
# include <map>
# include <list>
# include <stdexcept>

//base class for any attribute
//root
//server
//location etc..
class Attribute
{
	public:
		virtual void	handle_args(std::list<std::string> args) = 0;
		virtual Attribute& handle_keyword(std::string key)
		{
			(void)key;
			throw std::runtime_error("Error: body encountered for attribute that doesnt expect a body");
		}
		Attribute() : keywords() {}
		virtual ~Attribute() {}
		//keywords that the attribute responds to for parsing
		std::vector<std::string>	keywords;
//	protected:
};

#endif
