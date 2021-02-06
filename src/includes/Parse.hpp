/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Parse.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:56:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 00:34:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

# include <list>
# include <string>
# include <queue>
# include "Attribute.hpp"

class Parse
{
	public:
		Parse(Attribute& attr, std::list<std::string> args, std::list<std::string> tokens);
		Parse(const Parse& other);
		void	parse();
	private:
		std::list<std::string>::iterator	endOfBlock(std::list<std::string>::iterator start, std::list<std::string>::iterator end);

		Attribute&							attr;
		std::list<std::string>				args;
		std::list<std::string>				tokens;
		std::queue<Parse>					children;
};

#endif
