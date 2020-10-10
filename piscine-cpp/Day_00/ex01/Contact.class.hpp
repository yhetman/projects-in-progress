/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <yhetman@student.unit.ua>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:22:32 by yhetman           #+#    #+#             */
/*   Updated: 2019/12/03 19:54:11 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

# include <string>
# include <iostream>
# include <iomanip>

#define WIDTH	10

class Contact {

	public:
	
		Contact();
		~Contact();
	
		void		edit_contact(int index, std::string info);
		std::string	find_contact(int index);
	
	public:
		std::string	_info[11];
};

void	output_phonebook(Contact *contacts, int total);

#endif
