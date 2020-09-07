/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 00:03:24 by yhetman           #+#    #+#             */
/*   Updated: 2019/12/03 18:03:53 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "Contact.class.hpp"

Contact			add_contact(void)
{
	int			i;
	Contact		new_member;
	std::string	respond;

	i = 0;
	std::cout << "|\tFIRST NAME >> ";
	std::cin >> respond;
	new_member.edit_contact(i, respond);
	std::cout << "|\tLAST NAME >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tNICKNAME >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tLOGIN >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tPOSTAL ADDRESS >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tEMAIL ADDRESS >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tPHONE NUMBER >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tBIRTHDAY >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tFAVOURITE MEAL >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tUNDERWEAR COLOR >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	std::cout << "|\tDARKEST SECRET >> ";
	std::cin >> respond;
	new_member.edit_contact(++i, respond);
	return (new_member);
}

int				compare_input(std::string input, int *total, Contact *contacts)
{
	if (input.compare("ADD") == 0)
	{
		if (*total < 8)
		{
			contacts[*total] = add_contact();
			(*total)++;
		}
		else
			std::cout << "|==> Sorry! Phonebook is full!" << std::endl;
	}
	else if (input.compare("SEARCH") == 0)
	{
		if (*total > 0)
			output_phonebook(contacts, *total);
		else
			std::cout << "|==> Phonebook is empty!" << std::endl;
	}
	else if (input.compare("EXIT") == 0)
		return (1);
	return (0);
}

int			main(void)
{
	int total;
	std::string input = " ";

	total = 0;
	Contact contacts[8];
	std::cout << "|===============================|" << std::endl;
	std::cout << "|\tWELCOME TO PHONEBOOK\t|" << std::endl;
	std::cout << "|===============================|" << std::endl;
	while (true)
	{
		std::cout << "|===============================|" << std::endl;
		std::cout << "|\t  ALLOWED OPTIONS  \t|" << std::endl;
		std::cout << "|\tADD - SEARCH - EXIT\t|" << std::endl;
		std::cout << "|===============================|" << std::endl;
		std::cin >> input;
		std::cin.clear();
		if (compare_input(input, &total, contacts))
			return (0);
	}
	return (0);
}
