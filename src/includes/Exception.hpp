/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Exception.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 20:00:05 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/09 20:00:05 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <iostream>
# include <string>

namespace ft {

	class reqException {

	public:
		reqException(int status_code);
		reqException(const reqException& src);
		reqException& operator=(const reqException& rhs);
		~reqException();

		int getCode() const;
	private:
		int 	_code;
	};
}

#endif
