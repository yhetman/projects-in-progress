/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_phonebook.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 22:26:36 by yhetman           #+#    #+#             */
/*   Updated: 2019/12/03 19:54:19 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"

static void	particular_contact(Contact *contacts, int nbr_contacts)
{
	int		index;
	int		i;

	std::cout << "|==> Choose index of a contact >> ";
	std::cin >> index;
	if (std::cin.good() && (index >= 0 && index < nbr_contacts))
	{
		i = 0;
		while (i < 11)
			std::cout << contacts[index].find_contact(i++) << std::endl;
	}
	else
	{
    	std::cin.clear();
    	std::cout << "|==> Sorry! There's no such index!" << std::endl;
	}
}

static std::string	fill_spaces(std::string spaces)
{
	spaces = spaces.erase((WIDTH - 1),
			spaces.length() - (WIDTH - 1));
	spaces.append(".");
	return (spaces);
}

void	output_phonebook(Contact *contacts, int total)
{
	int				index;
	std::string     first;
	std::string     last;
	std::string     nick;

	index = -1;
    std::cout << std::setw(WIDTH);
	std::cout << "|     Index|First name| Last name|  Nickname|" << std::endl;
	while (++index < total)
	{
		first = contacts[index].find_contact(0);
		last = contacts[index].find_contact(1);
		nick = contacts[index].find_contact(2);
		std::cout << "|" << std::setw(WIDTH) << index;
		first = (first.length() > WIDTH)
			? fill_spaces(first) : first;
		std::cout << "|" << std::setw(WIDTH) << first;
		last = (last.length() > WIDTH)
			? fill_spaces(last) : last;
		std::cout << "|" << std::setw(WIDTH) << last;
		nick = (nick.length() > WIDTH)
			? fill_spaces(nick) : nick;
		std::cout << "|" << std::setw(WIDTH) << nick;
	    std::cout << "|" << std::endl;
	 }
	particular_contact(contacts, total);
}
