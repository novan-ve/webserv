/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Method.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:32:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/16 16:15:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHOD_HPP
# define METHOD_HPP

# include "EnumString.hpp"
# include <string>

enum	e_method
{
	OPTIONS,
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	TRACE,
	CONNECT,
	E_METHOD_END
};

class	Method : public EnumString<e_method>
{
	public:
		Method(e_method id);
		Method(std::string str);
		Method(const Method& other);
		virtual ~Method();
		Method& operator = (const Method& other); //everything is const

	private:
		Method();
		static const char * const names[]; //needed for EnumString, declared in cpp
};

#endif
