/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Exception.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: novan-ve <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/09 20:00:05 by novan-ve      #+#    #+#                 */
/*   Updated: 2021/02/11 10:43:22 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

# include <iostream>
# include <string>

namespace ft {

	class runtime_error
	{
		public:
			explicit runtime_error(const char *message);
			runtime_error(const runtime_error& other);
			runtime_error& operator = (const runtime_error& other);
			~runtime_error();
			const char *what() const;
		private:
			std::string _message;
	};

//-------------------------------------------------------------------

	class reqException {

	public:
		explicit reqException(const char *message, int status_code);
		reqException(const reqException& src);
		reqException& operator=(const reqException& rhs);
		~reqException();

		int getCode() const;
		const char *what() const;
	private:
		std::string _message;
		int 	_code;
	};
}

#endif
