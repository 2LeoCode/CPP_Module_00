/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 00:26:27 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 00:07:45 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <fstream>
# include <iterator>
# include <cstdio>
# include <csignal>
# include <cstdarg>
# include <unistd.h>

# define SPECIAL_CHARS "\001\002\003\004\005\006\007\010\011\012\013\014\015\
\016\017\020\021\022\023\024\025\026\027\030\031 !\"#$%&\'()*+,./:\
;<=>?@[\\]^_`{|}~\177"

extern bool quit;

struct				encryptKey
{
	std::uint64_t	*key;
	std::uint32_t	size;
};

struct				contact
{
	encryptKey		name;
	std::uint32_t	number;
};

bool				isValidNumber(std::string s);
bool				compareN(std::string s1, int n, ...);
encryptKey			encrypt(std::string key);
std::string			decrypt(encryptKey encryptionKey);
namespace			ft
{
	std::string		strToUpper(std::string &s);
	inline void		toupper(char &c)
	{
		c -= 32 * !!islower(c);
	}
}
class	PhoneBook
{
	public:

	PhoneBook(std::string pass, contact **contact);
	~PhoneBook(void);
	void			command(std::string cmd);


	private:

	void			add(void);
	void			remove(void);
	void			search(void);

	std::string		_pass;
	contact			**_contact;
};

typedef void		(PhoneBook::*cmd_ft)(void);

#endif
