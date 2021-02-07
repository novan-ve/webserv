/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Parse.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:58:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 23:02:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"
#include "Attribute.hpp"
#include "Configuration.hpp"
#include "Utilities.hpp"

#include <vector>
#include <map>
#include <string>
#include <queue>
#include <algorithm>
#include <stdexcept>
#include <iostream>

Parse::Parse(Attribute& attr, std::list<std::string> args, std::list<std::string> tokens) : attr(attr), args(args), tokens(tokens) {}

Parse::Parse(const Parse& other) : attr(other.attr), args(other.args), tokens(other.tokens) {}

//KEY [ARGS] (; | { [KEYS] })

void	Parse::parse()
{
	std::list<std::string>	childrenTokens;
	if (args.size())
		attr.handle_args(args);
		//actually does stuff to the properties

	std::cout << "TOKENS: ";
	ft::print_iteration(tokens.begin(), tokens.end());
	for (std::list<std::string>::iterator it = tokens.begin(); it != tokens.end();)
	{
//		std::cout << "Key: " << *it << std::endl;
		//if it's a known keyword
		if (find(attr.keywords.begin(), attr.keywords.end(), *it) != attr.keywords.end())
		{
//			std::cout << "KEYWORD FOUND!" << std::endl;
			std::string		key = *it++;
			bool			body = false;
			args.clear();
			for (; it != tokens.end(); it++)
			{
				if (*it == "{" || *it == ";")
				{
					body = (*it == "{");
					break ;
				}
				args.push_back(*it);
			}
			if (body)
			{
				it++;
				childrenTokens.clear();
//				std::cout << "KEY HAS BODY" << std::endl;
				std::list<std::string>::iterator	end = this->endOfBlock(it, tokens.end());
				if (end == tokens.end())
					throw std::runtime_error("Error: Unclosed block in configuration");

				childrenTokens.splice(childrenTokens.begin(), this->tokens, it--, end);
				it++;
			}
			it++;
			//only creates attributes. (handle_keyword);
			this->children.push(Parse(attr.handle_keyword(key), args, childrenTokens));
		}
		else
			throw std::runtime_error("Error: unrecognized keyword in config-parser");
//		it++;
	}
	while (this->children.size())
	{
		this->children.front().parse();
		this->children.pop();
	}
}

std::list<std::string>::iterator	Parse::endOfBlock(std::list<std::string>::iterator start, std::list<std::string>::iterator end)
{
	size_t depth = 0;

	for (;start != end; start++)
	{
		if (*start == "}")
		{
			if (!depth)
				break ;
			depth--;
		}
		else if (*start == "{")
			depth++;
	}
	return (start);
}
