/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:38:49 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 21:45:04 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
# define HEADER_HPP

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
# define EMAIL_INV_CHARS "\001\002\003\004\005\006\007\010\011\012\013\014\015\
\016\017\020\021\022\023\024\025\026\027\030\031 !\"#$%&\'()*+,-/:\
;<=>?[\\]^_`{|}~\177"
# define ADDRESS_INV_CHARS "\001\002\003\004\005\006\007\010\011\012\013\014\015\
\016\017\020\021\022\023\024\025\026\027\030\031!\"#$%&\'()*+./:\
;<=>?@[\\]^_`{|}~\177"
# define NICK_INV_CHARS "\001\002\003\004\005\006\007\010\011\012\013\014\015\
\016\017\020\021\022\023\024\025\026\027\030\031!\"#$%&\'()*+,-./:\
;<=>?@[\\]^_`{|}~\177"

extern bool				quit;

struct					encryptKey
{
	std::uint64_t		*key;
	std::uint32_t		size;
};

bool					isValidNumber(std::string s);
bool					compareN(std::string s1, int n, ...);
encryptKey				encrypt(std::string key);
std::string				decrypt(encryptKey encryptionKey);
namespace				ft
{
	bool				strIsAlpha(std::string s);
	bool				strIsDigit(std::string s);
	std::string			strToUpper(std::string &s);
	inline std::string	truncate(std::string s, std::uint32_t size)
	{
		return ((s.length() > size) ? (s.substr(0, size - 1) + '.') : s);
	}
	inline void			toupper(char &c)
	{
		c -= 32 * !!islower(c);
	}
}

#endif
