/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Method.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/02 19:32:14 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/02 20:59:33 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHOD_HPP
# define METHOD_HPP

#include <string>

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

class	Method
{
	public:
		Method(e_method id);
		Method(std::string str);
		Method(const Method& other);
		Method& operator = (const Method& other);
		~Method();

		e_method		id;
		std::string		str;
	private:
		Method(); //fuck 42s coplien
		e_method		toId();
		std::string		toString();
};

#endif
