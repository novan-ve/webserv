/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Exception.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 20:03:43 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/11 10:47:18 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.hpp"

namespace ft {

	runtime_error::runtime_error(const char *message) : _message(message) {}
	runtime_error::runtime_error(const runtime_error& other) : _message(other._message) {}
	runtime_error& runtime_error::operator=(const runtime_error& other)
	{
		if (this != &other)
		{
			this->_message = other._message;
		}
		return *this;
	}
	runtime_error::~runtime_error() {}
	const char *runtime_error::what() const { return this->_message.c_str(); }

//-----------------------------------------------------------------------------------------------

	reqException::reqException(const char *message, int status_code) : _message(message), _code(status_code) {}

	reqException::reqException(const reqException& src) {
		*this = src;
	}

	reqException& reqException::operator=(const reqException& rhs) {

		if (this != &rhs)
		{
			this->_code = rhs._code;
			this->_message = rhs._message;
		}
		return *this;
	}

	reqException::~reqException() {}

	int reqException::getCode() const { return this->_code; }
	const char *reqException::what() const { return this->_message.c_str(); }
}
