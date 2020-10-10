/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:29:28 by yhetman           #+#    #+#             */
/*   Updated: 2019/12/03 17:13:06 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"

Contact::Contact()
{
	return ;
}

Contact::~Contact()
{
	return ;
}

void		Contact::edit_contact(int index, std::string info) 
{
	if (index >= 0 && index < 11)
		this->_info[index] = info;
}

std::string	Contact::find_contact(int index)
{
	if (index < 11 && index >= 0)
		return (this->_info[index]);
	return ("ERROR!");
}
