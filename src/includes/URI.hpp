/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   URI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:22:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/04 18:09:43 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_HPP
# define URI_HPP

# include <vector>
# include <string>

enum	e_uri
{
	URI_SCHEME,
	URI_HOST,
	URI_PORT,
	URI_PATH,
	URI_QUERY,
	URI_FRAGMENT_ID
};

class URI
{
	public:
		URI(const std::string& uri);
		URI(const URI& other);
		URI& operator = (const URI& other);
		~URI();
	private:
		URI();
		std::vector<std::string>	parts;
};

#endif
