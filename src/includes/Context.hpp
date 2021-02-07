/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Context.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/05 18:35:46 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/07 16:59:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP
# define CONTEXT_HPP

# include "Properties.hpp"

# include <vector>
# include <list>
# include <string>
# include <map>

class Context
{
	private:
		typedef Context *(Context::*keyword_func)(const std::list<std::string>& args);

		Context *key_server(const std::list<std::string>& args);
		Context	*key_location(const std::list<std::string>& args);
		Context	*key_listen(const std::list<std::string>& args);
		Context *key_server_name(const std::list<std::string>& args);
		Context *key_client_max_body_size(const std::list<std::string>& args);
		Context *key_root(const std::list<std::string>& args);
		Context *key_error_page(const std::list<std::string>& args);
		Context *key_limit_except(const std::list<std::string>& args);
		Context *key_index(const std::list<std::string>& args);
		Context *key_autoindex(const std::list<std::string>& args);
	protected:
		Context&					parent;
		Properties					properties;
		std::vector<Context*>		children;
	public:
		std::vector<std::string>	keywords;
		Context	*parse_keyword(std::string key, std::list<std::string> args);
		Context();
		Context(Context& other);
		virtual ~Context();
};

#endif
