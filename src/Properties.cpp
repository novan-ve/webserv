/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Properties.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 09:37:47 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 09:45:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "Properties.hpp"

Properties::Properties() {}

Properties::Properties(const Properties& other) : values(other.values) {}
