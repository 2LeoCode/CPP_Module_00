/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:23:45 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 21:44:52 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"
#include "header.hpp"

bool quit = false;

bool			ft::strIsAlpha(std::string s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (!std::isalpha(*it))
			return (false);
	return (true);
}

bool			ft::strIsDigit(std::string s)
{
	for (std::string::iterator it = s.begin(); it != s.end(); it++)
		if (!std::isdigit(*it))
			return (false);
	return (true);
}

std::string		ft::strToUpper(std::string &s)
{
	for (int i = 0; s[i]; i++)
		ft::toupper(s[i]);
	return (s);
}

bool			isValidNumber(std::string s)
{
	if (s.length() != 10)
		return (false);
	for (int i = 0; i < 10; i++)
		if ((s[i] < '0') || (s[i] > '9'))
			return (false);
	return (true);
}

bool			compareN(std::string s1, int n, ...)
{
	va_list		args;
	bool		ret = true;

	va_start(args, n);
	for (int i = 0; i < n; i++)
		if (!s1.compare(va_arg(args, char*)))
			ret = false;
	va_end(args);
	return (ret);
}

encryptKey		encrypt(std::string key)
{
	encryptKey		encryptionKey;
	int				i = 0;

	encryptionKey.size = (key.length() / 9) + !!(key.length() % 9);
	encryptionKey.key = new std::uint64_t[encryptionKey.size];
	for (std::string::iterator it = key.begin(); it != key.end(); it++)
	{
		if (!(std::distance(key.begin(), it) % 9))
		{
			if (std::distance(key.begin(), it))
				i++;
			encryptionKey.key[i] = 0;
		}
		encryptionKey.key[i] *= 128, encryptionKey.key[i] += *it;
	}
	return (encryptionKey);
}

std::string		decrypt(encryptKey encryptionKey)
{
	std::string		key;
	std::uint64_t	tmp;

	for (int i = (encryptionKey.size - 1); i >= 0; i--)
	{
		tmp = encryptionKey.key[i];
		while (tmp)
			key.insert(key.begin(), tmp % 128), tmp /= 128;
	}
	return (key);
}

void			sigHandler(int)
{
	quit = true;
	std::cout << std::endl << "INTERRUPT" << std::endl;
	close(0);
}

int				main(void)
{
	std::ifstream		in("PhoneBook.data", std::ios::in | std::ios::binary);
	char				dummy;
	std::ofstream		out;
	std::string			pass, cmd;
	encryptKey			key;
	Contact				**contacts = new Contact*[8];

	for (int i = 0; i < 8; i++)
		contacts[i] = nullptr;
	std::signal(SIGINT, sigHandler);
	if (in.fail())
	{
		do
		{
			std::cout << ">CHOOSE A PASSWORD:";
			std::getline(std::cin, pass);
			if (quit)
				return (0);
			if (pass.length() < 5)
				std::cout << "PASSWORD MUST BE AT LEAST 5 CHARACTERS LONG" << std::endl;
		}
		while (pass.length() < 5);
		key = encrypt(pass);
		in.open("PhoneBook.data", std::ios::in | std::ios::binary);
	}
	else
	{
		in.read((char*)&key.size, sizeof(std::uint32_t));
		key.key = new std::uint64_t[key.size];
		in.read((char*)key.key, sizeof(std::uint64_t) * key.size);
		pass = decrypt(key);
		for (int i = 0; (i < 8); i++)
		{
			in.read(&dummy, 1);
			if (in.eof())
				break ;
			in.seekg(-1, in.cur);
			contacts[i] = new Contact(&in);
		}
	}
	in.close();

	PhoneBook		pb(pass, contacts);

	while (!quit)
	{
		std::cout << ">";
		std::getline(std::cin, cmd);
		pb.command(cmd);
	}
	out.open("PhoneBook.data", std::ios::trunc | std::ios::binary);
	out.write((char*)&key.size, sizeof(std::uint32_t));
	out.write((char*)key.key, sizeof(std::uint64_t) * key.size);
	delete[] key.key;
	for (int i = 0; (i < 8) && contacts[i]; i++)
	{
		encryptKey	eKey = encrypt(contacts[i]->getFirstName());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * key.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getLastName());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getLogin());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getNickName());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getPostal());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getEmail());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getFav());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getUnder());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		eKey = encrypt(contacts[i]->getDarkest());
		out.write((char*)&eKey.size, sizeof(std::uint32_t));
		out.write((char*)eKey.key, sizeof(std::uint64_t) * eKey.size);
		delete[] eKey.key;
		out.write((char*)&contacts[i]->getMonth(), sizeof(std::uint32_t));
		out.write((char*)&contacts[i]->getDay(), sizeof(std::uint32_t));
		out.write((char*)&contacts[i]->getYear(), sizeof(std::uint32_t));
		out.write((char*)&contacts[i]->getNumber(), sizeof(std::uint32_t));
		delete contacts[i];
	}
	delete[] contacts;
	out.close();
	return (0);
}
