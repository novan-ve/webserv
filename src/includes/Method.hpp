/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Method.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:32:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 15:17:57 by tbruinem      ########   odam.nl         */
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
	CONNECT
};

class	Method : public EnumString<e_method>
{
	public:
		Method(e_method id);
		Method(std::string str);
		Method(const Method& other);
		~Method();

	private:
		Method(); //fuck 42s coplien
		static const char * const names[]; //needed for EnumString, declared in cpp
		Method& operator = (const Method& other); //everything is const
};

#endif
