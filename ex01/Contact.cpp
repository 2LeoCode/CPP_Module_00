/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:40:40 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 20:47:33 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(std::ifstream *file) : _nickname(""), _first_name(""), _last_name(""),
_login(""), _postal_address(""), _email_address(""), _favorite_meal(""), _underwear_color(""),
_darkest_secret(""), _month_of_birth(0), _day_of_birth(0), _year_of_birth(0), _number(0)
{
	if (!file)
	{
		_number = 0;
		return ;
	}
	encryptKey	key;

	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_first_name = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_last_name = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_login = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_nickname = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_postal_address = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_email_address = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_favorite_meal = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_underwear_color = decrypt(key);
	delete[] key.key;
	file->read((char*)&key.size, sizeof(std::uint32_t));
	key.key = new std::uint64_t[key.size];
	file->read((char*)key.key, sizeof(std::uint64_t) * key.size);
	_darkest_secret = decrypt(key);
	delete[] key.key;
	file->read((char*)&_month_of_birth, sizeof(std::uint32_t));
	file->read((char*)&_day_of_birth, sizeof(std::uint32_t));
	file->read((char*)&_year_of_birth, sizeof(std::uint32_t));
	file->read((char*)&_number, sizeof(std::uint32_t));
}

Contact::~Contact(void)
{
}
