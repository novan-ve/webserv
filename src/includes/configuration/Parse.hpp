/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Parse.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:56:00 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/16 20:11:12 by tbruinem      ########   odam.nl         */
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
		Parse(Context* context, std::list<std::string> tokens);
		Parse(const Parse& other);
		Parse& operator=(const Parse& other);
		virtual ~Parse();
		void	parse();
	private:
		Parse();
		bool								collect_args(std::list<std::string>::iterator& it, std::list<std::string>::iterator end, std::list<std::string>& args);
		std::list<std::string>::iterator	endOfBlock(std::list<std::string>::iterator start, std::list<std::string>::iterator end);
		void								handle_body(std::queue<Parse>& children, Context* child, std::list<std::string>::iterator& it, std::list<std::string>& tokens);
		Context*							context;
		std::list<std::string>				tokens;
};

#endif
