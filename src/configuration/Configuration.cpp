/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Configuration.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/03 18:51:51 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/03/26 17:50:21 by novan-ve      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"
#include "Utilities.hpp"
#include "WebServer.hpp"
#include "Server.hpp"
#include "Parse.hpp"
#include "WebServer.hpp"

#include <fcntl.h>
#include <string>
#include <list>

//open the config or revert back to the default config file
Configuration::Configuration(char *config, WebServer* webserv) : webserv(webserv)
{
	if (!config)
		config = (char *)DEFAULT_CONFIG;
	this->fd = open(config, O_RDONLY);
	if (this->fd == -1 || read(this->fd, NULL, 0) == -1)
		throw std::runtime_error("Error: Failed to open config file for reading");
}

Configuration::Configuration(const Configuration & src) : webserv(src.webserv)
{
	*this = src;
}

Configuration&	Configuration::operator=(const Configuration & rhs)
{
	if (this != &rhs)
	{
		this->fd = rhs.fd;
		this->webserv = rhs.webserv;
	}

	return *this;
}

void	strip_comments(std::string& config)
{
	size_t	start = std::string::npos;
	bool	entire_line = false;

	for (size_t i = 0; i < config.size();)
	{
		if (start == std::string::npos && config[i] == '#')
		{
			entire_line = (!i || config[i - 1] == '\n');
			start = i++;
		}
		else if (start != std::string::npos && config[i] == '\n')
		{
			config.erase(start, i + entire_line - start);
			i = start;
			start = std::string::npos;
		}
		else
			i++;
	}
	if (start != std::string::npos)
		config.erase(start, config.size());
}

void	Configuration::populateTokens(std::list<std::string>& tokens)
{
	std::string	raw_content;

	char	*buffer[BUFFER_SIZE + 1];
	int 	bytes_read = 0;

	//read raw content
	while (1)
	{
		raw_content += std::string((char *)buffer, bytes_read);
		bytes_read = read(this->fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			throw std::runtime_error("Error: failed to read config file");
		if (!bytes_read)
			break ;
	}
	strip_comments(raw_content);
	std::vector<std::string>	vec_tokens = ft::split(raw_content, "\n\t\r {};", "{};");
	tokens = std::list<std::string>(vec_tokens.begin(), vec_tokens.end());
}

void	Configuration::checkMultiplePorts(void) const
{
		// Check for multiple server_blocks with the same port and server_name
	std::map<std::string, const Properties*>	ports;
	for (size_t i = 0 ; i < this->webserv->children.size(); i++)
	{
		if (ports.count(this->webserv->children[i]->get_properties().ip_port.second))
		{
			for (std::vector<std::string>::const_iterator it = this->webserv->children[i]->get_properties().server_names.begin();
				 it != this->webserv->children[i]->get_properties().server_names.end(); it++)
			{
				std::vector<std::string> tmp = ports[this->webserv->children[i]->get_properties().ip_port.second]->server_names;
				if (std::find(tmp.begin(), tmp.end(), *it) != tmp.end())
					throw std::runtime_error("Error: detected multiple servers with the same port");
			}
		}
		if (!this->webserv->children[i]->get_properties().ip_port.second.empty())
			ports[this->webserv->children[i]->get_properties().ip_port.second] = &this->webserv->children[i]->get_properties();
	}
}

//parse the config into Servers
void	Configuration::parse()
{
	std::list<std::string>	tokens;
	populateTokens(tokens);
	std::list<std::string>	arguments;
	Parse(this->webserv, tokens).parse();
	checkMultiplePorts();
	std::cout << "Configuration loaded" << std::endl;
}

Configuration::~Configuration()
{
	close(this->fd);
}

Configuration::Configuration() : webserv(NULL) {}
