/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Scope.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/06 09:33:44 by tbruinem      #+#    #+#                 */
/*   Updated: 2021/02/06 13:11:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Attribute.hpp"
#include "Scope.hpp"
#include "Properties.hpp"

//Parent scope
Scope::Scope() : Attribute(*this), parent(*this), properties() {}

//Child scope
Scope::Scope(Scope& parent) : Attribute(parent.scope), parent(parent), properties(parent.properties) {}

Scope::~Scope() {}
