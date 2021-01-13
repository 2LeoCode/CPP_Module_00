/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:23:45 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 00:07:27 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

bool quit = false;

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
	std::cout << std::endl << ">INTERRUPT" << std::endl;
	close(0);
}

int				main(void)
{
	std::ifstream		in("PhoneBook.data", std::ios::in | std::ios::binary);
	char				dummy;
	std::ofstream		out;
	std::string			pass, cmd;
	encryptKey			key;
	contact				**contacts = new contact*[8];

	for (int i = 0; i < 8; i++)
		contacts[i] = nullptr;
	std::signal(SIGINT, sigHandler);
	if (in.fail())
	{
		do
		{
			std::cout << ">Choose a password:";
			std::getline(std::cin, pass);
			if (quit)
				return (0);
			if (pass.length() < 5)
				std::cout << ">Password must be at least 5 characters long" << std::endl;
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
			contacts[i] = new contact;
			in.read((char*)&contacts[i]->name.size, sizeof(std::uint32_t));
			contacts[i]->name.key = new std::uint64_t[contacts[i]->name.size];
			in.read((char*)contacts[i]->name.key, sizeof(std::uint64_t) * contacts[i]->name.size);
			in.read((char*)&contacts[i]->number, sizeof(std::uint32_t));
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
		out.write((char*)&contacts[i]->name.size, sizeof(std::uint32_t));
		out.write((char*)contacts[i]->name.key, sizeof(std::uint64_t) * contacts[i]->name.size);
		out.write((char*)&contacts[i]->number, sizeof(std::uint32_t));
		delete[] contacts[i]->name.key;
		delete contacts[i];
	}
	delete[] contacts;
	out.close();
	return (0);
}
