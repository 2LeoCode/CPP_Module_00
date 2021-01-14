/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:26:27 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 10:41:20 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "header.hpp"
# include "Contact.hpp"

class	PhoneBook
{
	public:

	PhoneBook(std::string pass, Contact **contact);
	~PhoneBook(void);
	void			command(std::string cmd);


	private:

	void			add(void);
	void			remove(void);
	void			search(void);

	std::string		_pass;
	Contact			**_contact;
};

typedef void		(PhoneBook::*cmd_ft)(void);

#endif
