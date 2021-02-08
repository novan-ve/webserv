/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   URI.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/04 17:22:59 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/08 11:57:36 by tbruinem      ########   odam.nl         */
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
	URI_FRAGMENT_ID,
	URI_FULL
};

class URI
{
	public:
		friend class PartModifier;
		class PartModifier
		{
			private:
				URI& uri;
				e_uri id;
				std::string &str;
			public:
				PartModifier(URI& uri, std::string& part, e_uri id);
				void	operator () (std::string updated);	
		};

		const std::string& operator [] (e_uri id); //get reference
		PartModifier operator [] (std::string part); //change the URI

		const std::string&			get_uri();
		const std::string&			get_scheme();
		const std::string&			get_host();
		const std::string&			get_port();
		const std::string&			get_path();
		const std::string&			get_query();
		const std::string&			get_fragment();
		std::vector<std::string>	get_parts();

		void						set_uri(std::string updated);
		void						set_scheme(std::string updated);
		void						set_host(std::string updated);
		void						set_port(std::string updated);
		void						set_path(std::string updated);
		void						set_query(std::string updated);
		void						set_fragment(std::string updated);
		void						set_parts(const std::vector<std::string>& updated);

		URI(const std::string& uri);
		URI(const URI& other);
		URI& operator = (const URI& other);
		~URI();
	private:
		void	print_state();
		URI();
		std::string					str;
		std::vector<std::string>	parts;
};

#endif
