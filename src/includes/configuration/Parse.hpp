/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Parse.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:56:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/07 16:22:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

# include <list>
# include <string>
# include <queue>
# include "Context.hpp"

class Parse
{
	public:
		Parse(Context& context, std::list<std::string> tokens);
		Parse(const Parse& other);
		void	parse();
	private:
		std::list<std::string>::iterator	endOfBlock(std::list<std::string>::iterator start, std::list<std::string>::iterator end);

		Context&							context;
		std::list<std::string>				tokens;
		std::queue<Parse>					children;
};

#endif
