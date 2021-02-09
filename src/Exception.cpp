/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Exception.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 20:03:43 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/09 20:03:44 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Exception.hpp"

namespace ft {

	reqException::reqException(int status_code) : _code(status_code) {}

	reqException::reqException(const reqException& src) {
		*this = src;
	}

	reqException& reqException::operator=(const reqException& rhs) {

		if (this != &rhs)
			this->_code = rhs._code;
		return *this;
	}

	reqException::~reqException() {}

	int reqException::getCode() const { return this->_code; }
}
