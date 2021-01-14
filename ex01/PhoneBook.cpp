/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:02:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 21:30:21 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(std::string pass, Contact **contact) : _pass(pass), _contact(contact)
{
	std::string		password;

	do
	{
		std::cout << ">ENTER PASSWORD:";
		std::getline(std::cin, password);
		if (quit)
			return ;
		if (password.compare(_pass))
			std::cout << "WRONG PASSWORD" << std::endl;
	}
	while (password.compare(_pass));
}

PhoneBook::~PhoneBook(void)
{
}

void	PhoneBook::command(std::string cmd)
{
	if (!cmd.compare("EXIT"))
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
	std::string		name, input;
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
			std::cout << '>' << (i + 1) << " - " << _contact[i]->getNickName() << std::endl;
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
		delete _contact[ind];
	}
	_contact[ind] = new Contact;
	std::cout << ">ENTER NEW CONTACT FIRST NAME:";
	while ((name.length() < 2) || !ft::strIsAlpha(name))
	{
		std::getline(std::cin, name);
		if (quit)
			goto interrupt;
		if ((name.length() < 2) || !ft::strIsAlpha(name))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setFirstName(ft::strToUpper(name));
	std::cout << ">ENTER " << name << "'S LAST NAME:";
	while ((input.length() < 2) || !ft::strIsAlpha(input))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || !ft::strIsAlpha(input))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setLastName(ft::strToUpper(input));
	std::cout << ">ENTER " << name << "\'S NUMBER:";
	input = "";
	while (!isValidNumber(input))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if (!isValidNumber(input))
			std::cout << ">NOT A VALID NUMBER, TRY AGAIN:";
	}
	_contact[ind]->setNumber((std::uint32_t)atol(input.c_str()));	
	std::cout << ">ENTER " << name << "\'S MONTH OF BIRTH [..]:";
	input = "";
	while ((input.length() > 2) || !input.length() || !ft::strIsDigit(input) || !std::atoi(input.c_str()) || (std::atoi(input.c_str()) > 12))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() > 2) || !input.length() || !ft::strIsDigit(input) || !std::atoi(input.c_str()) || (std::atoi(input.c_str()) > 12))
			std::cout << ">[1 - 12][..]:";
	}
	_contact[ind]->setMonth((std::uint32_t)atol(input.c_str()));
	std::cout << ">ENTER " << name << "\'S DAY OF BIRTH [..]:";
	input = "";
	while ((input.length() > 2) || !input.length() || !ft::strIsDigit(input) || !std::atoi(input.c_str()) || (std::atoi(input.c_str()) > 31))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() > 2) || !input.length() || !ft::strIsDigit(input) || !std::atoi(input.c_str()) || (std::atoi(input.c_str()) > 31))
			std::cout << ">[1 - 31][..]:";
	}
	_contact[ind]->setDay((std::uint32_t)atol(input.c_str()));
	std::cout << ">ENTER " << name << "\'S YEAR OF BIRTH [....]:";
	input = "";
	while ((input.length() != 4) || !ft::strIsDigit(input))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() != 4) || !ft::strIsDigit(input))
			std::cout << ">[....]:";
	}
	_contact[ind]->setYear((std::uint32_t)atol(input.c_str()));
	std::cout << ">ENTER " << name << "'S NICK NAME:";
	input = "";
	while ((input.length() < 2) || (input.find_first_of(NICK_INV_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || (input.find_first_of(NICK_INV_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setNickName(ft::strToUpper(input));
	std::cout << ">ENTER " << name << "'S LOGIN:";
	input = "";
	while ((input.length() < 2) || (input.find_first_of(SPECIAL_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || (input.find_first_of(SPECIAL_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z][0 - 9]:";
	}
	_contact[ind]->setLogin(input);
	std::cout << ">ENTER " << name << "'S POSTAL ADDRESS:";
	input = "";
	while ((input.length() < 2) || (input.find_first_of(ADDRESS_INV_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || (input.find_first_of(ADDRESS_INV_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z][0 - 9]:";
	}
	_contact[ind]->setPostal(ft::strToUpper(input));
	std::cout << ">ENTER " << name << "'S EMAIL ADDRESS:";
	input = "";
	while ((input.length() < 2) || (input.find_first_of(EMAIL_INV_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || (input.find_first_of(EMAIL_INV_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z][0 - 9]:";
	}
	_contact[ind]->setEmail(input);
	std::cout << ">ENTER " << name << "'S FAVORITE MEAL:";
	input = "";
	while ((input.length() < 2) || !ft::strIsAlpha(input))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || !ft::strIsAlpha(input))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setFav(ft::strToUpper(input));
	std::cout << ">ENTER " << name << "'S UNDERWEAR COLOR:";
	input = "";
	while ((input.length() < 2) || !ft::strIsAlpha(input))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if ((input.length() < 2) || !ft::strIsAlpha(input))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setUnder(ft::strToUpper(input));
	std::cout << ">ENTER " << name << "'S DARKEST SECRET:";
	input = "";
	while (!input.length() || (input.find_first_of(NICK_INV_CHARS) != std::string::npos))
	{
		std::getline(std::cin, input);
		if (quit)
			goto interrupt;
		if (!input.length() || (input.find_first_of(NICK_INV_CHARS) != std::string::npos))
			std::cout << ">[a - z][A - Z]:";
	}
	_contact[ind]->setDark(ft::strToUpper(input));
	std::cout << "ADDED CONTACT" << std::endl;
	return ;
	interrupt:
	delete _contact[ind];
	_contact[ind] = nullptr;
}

void	PhoneBook::remove(void)
{
	std::string		input;
	int				nb;

	for (int i = 0; (i < 8) && _contact[i]; i++)
	{
		std::cout << std::setw(10) << (i + 1) << '|' << std::setw(10) << ft::truncate(_contact[i]->getFirstName(), 10) <<\
		'|' << std::setw(10) << ft::truncate(_contact[i]->getLastName(), 10) << '|' << std::setw(10) << ft::truncate(_contact[i]->getLogin(), 10) << std::endl;
	}
	std::cout << ">ENTER THE INDEX OF THE CONTACT TO REMOVE:";
	std::getline(std::cin, input);
	if (ft::strIsDigit(input) && (nb = std::atoi(input.c_str())) && (nb < 9))
	{
		delete _contact[--nb];
		for (int i = nb; i < 7; i++)
			_contact[i] = _contact[i + 1];
		_contact[7] = nullptr;
		std::cout << "REMOVED " << input << std::endl;
	}
	else
		std::cout << "WRONG INPUT" << std::endl;
}

void	PhoneBook::search(void)
{
	std::string		input;
	int				nb;
	int				i;

	for (i = 0; (i < 8) && _contact[i]; i++)
	{
		std::cout << std::setw(10) << (i + 1) << '|' << std::setw(10) << ft::truncate(_contact[i]->getFirstName(), 10) <<\
		'|' << std::setw(10) << ft::truncate(_contact[i]->getLastName(), 10) << '|' << std::setw(10) << ft::truncate(_contact[i]->getLogin(), 10) << std::endl;
	}
	if (!i)
	{
		std::cout << "THERE IS NO CONTACT YET" << std::endl;
		return ;
	}
	std::cout << ">ENTER A CONTACT INDEX TO SEE DETAILS:";
	std::getline(std::cin, input);
	if (quit)
		return ;
	if (input.length() && ft::strIsDigit(input) && ((nb = (std::atoi(input.c_str()) - 1)) >= 0) && (nb < i))
	{
		std::cout << std::setw(15) << "FIRST NAME" << ' ' << _contact[nb]->getFirstName() <<\
		std::endl << std::setw(15) << "LAST NAME" << ' ' << _contact[nb]->getLastName() <<\
		std::endl << std::setw(15) << "LOGIN" << ' ' << _contact[nb]->getLogin() <<\
		std::endl << std::setw(15) << "NICKNAME" << ' ' << _contact[nb]->getNickName() <<\
		std::endl << std::setw(15) << "PHONE NUMBER" << ' ' << std::setw(10) << std::setfill('0') << _contact[nb]->getNumber() << std::setfill(' ') <<\
		std::endl << std::setw(15) << "EMAIL ADDRESS" << ' ' << _contact[nb]->getEmail() <<\
		std::endl << std::setw(15) << "POSTAL ADDRESS" << ' ' << _contact[nb]->getPostal() <<\
		std::endl << std::setw(15) << "BIRTHDAY" << ' ' << std::setw(2) << std::setfill('0') << _contact[nb]->getDay() << '/' << std::setw(2) << _contact[nb]->getMonth() << '/' << _contact[nb]->getYear() << std::setfill(' ') <<\
		std::endl << std::setw(15) << "FAVORITE MEAL" << ' ' << _contact[nb]->getFav() <<\
		std::endl << std::setw(15) << "UNDERWEAR COLOR" << ' ' << _contact[nb]->getUnder() <<\
		std::endl << std::setw(15) << "DARKEST SECRET" << ' ' << _contact[nb]->getDarkest() << std::endl;
	}
	else
		std::cout << "INVALID INPUT" << std::endl;
}
