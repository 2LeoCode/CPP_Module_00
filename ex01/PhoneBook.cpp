/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:02:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 00:02:52 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(std::string pass, contact **contact) : _pass(pass), _contact(contact)
{
	std::string		password;

	do
	{
		std::cout << ">Enter password:";
		std::getline(std::cin, password);
		if (quit)
			return ;
		if (password.compare(_pass))
			std::cout << ">Wrong password" << std::endl;
	}
	while (password.compare(_pass));
}

PhoneBook::~PhoneBook(void)
{
}

void	PhoneBook::command(std::string cmd)
{
	if (!cmd.compare("QUIT"))
		quit = true;
	if (quit == true)
		return ;

	std::string		command_str[3] = {"ADD", "REMOVE", "SEARCH"};
	cmd_ft			command_ft[3] = {&PhoneBook::add, &PhoneBook::remove, &PhoneBook::search};
	cmd_ft			*used_ft = nullptr;

	for (int i = 0; i < 3; i++)
		if (!cmd.compare(command_str[i]))
			used_ft = new cmd_ft(command_ft[i]);
	if (!used_ft)
		std::cout << "UNKNOWN INPUT" << std::endl;
	else
	{
		(this->**used_ft)();
		delete used_ft;
	}
}

void	PhoneBook::add(void)
{
	bool			full = true;
	std::string		input;
	int				ind = -1;

	for (int i = 0; i < 8; i++)
		if (!_contact[i])
		{
			full = false;
			ind = i;
			break ;
		}
	if (full)
	{
		std::cout << ">CONTACT LIST IS FULL" << std::endl << "DO YOU WISH TO REPLACE A CONTACT? (Y/n):";
		while (compareN(input, 4, "Y", "y", "N", "n"))
		{
			std::getline(std::cin, input);
			if (quit)
				return ;
			if (compareN(input, 4, "Y", "y", "N", "n"))
				std::cout << ">(Y/n):";
		}
		if (input[0] == 'N' || input[0] == 'n')
			return ;
		for (int i = 0; (i < 8) && _contact[i]; i++)
			std::cout << '>' << (i + 1) << " - " << decrypt(_contact[i]->name) << std::endl;
		std::cout << ">WHICH ONE DO YOU WANT TO REPLACE? [1 - 8]:";
		while (1)
		{
			std::getline(std::cin, input);
			if (quit)
				return ;
			if ((input.length() == 1) && (input[0] >= '1') && (input[0] <= '8'))
				break ;
			else 
				std::cout << ">[1 - 8]:";
		}
		ind = input[0] - 49;
		delete[] _contact[ind]->name.key;
	}
	else
		_contact[ind] = new contact;
	std::cout << ">ENTER NEW CONTACT NAME:";
	input = "";
	while ((input.length() < 2) || (input.find_first_of(SPECIAL_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			return ;
		if ((input.length() < 2) || (input.find_first_of(SPECIAL_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z][0 - 9]:";
	}
	_contact[ind]->name = encrypt(ft::strToUpper(input));
	_contact[ind]->number = 0;
	std::cout << ">ENTER " << input << "\'S NUMBER:";
	input = "";
	while (!isValidNumber(input))
	{
		std::getline(std::cin, input);
		if (quit)
			return ;
		if (!isValidNumber(input))
			std::cout << ">NOT A VALID NUMBER, TRY AGAIN:";
	}
	_contact[ind]->number = (std::uint32_t)atol(input.c_str());
	std::cout << "ADDED CONTACT" << std::endl;
}

void	PhoneBook::remove(void)
{
	bool			removed = false;
	std::string		input;

	std::cout << ">ENTER THE NAME OF THE CONTACT TO REMOVE:";
	while (!removed)
	{
		std::getline(std::cin, input);
		if (quit)
			return ;
		for (int i = 0; (i < 8) && _contact[i]; i++)
			if (!ft::strToUpper(input).compare(decrypt(_contact[i]->name)))
			{
				delete[] _contact[i]->name.key;
				delete _contact[i];
				for (int j = i; j < 7; j++)
					_contact[j] = _contact[j + 1];
				_contact[7] = nullptr;
				removed = true;
				break ;
			}
	}
	std::cout << "REMOVED " << input << std::endl;
}

void	PhoneBook::search(void)
{
	std::string		input;

	std::cout << ">ENTER A NAME TO SEARCH:";
	std::getline(std::cin, input);
	if (quit)
		return ;
	ft::strToUpper(input);
	for (int i = 0; (i < 8) && _contact[i]; i++)
		if (!input.compare(decrypt(_contact[i]->name)))
		{
			std::cout << input << ": " << std::setfill('0') << std::setw(10) << _contact[i]->number << std::endl;
			return ;
		}
	std::cout << input << " NOT FOUND" << std::endl;
}
