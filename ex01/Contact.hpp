/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 10:40:43 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/14 20:24:35 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include "header.hpp"

class Contact
{
	public:

	Contact(std::ifstream *file = nullptr);
	~Contact(void);

	inline void				setNickName(std::string nick)
	{
		_nickname = nick;
	}
	inline void				setNumber(std::uint32_t number)
	{
		_number = number;
	}
	inline void				setFirstName(std::string name)
	{
		_first_name = name;
	}
	inline void				setLastName(std::string name)
	{
		_last_name = name;
	}
	inline void				setLogin(std::string login)
	{
		_login = login;
	}
	inline void				setPostal(std::string add)
	{
		_postal_address = add;
	}
	inline void				setEmail(std::string mail)
	{
		_email_address = mail;
	}
	inline void				setFav(std::string meal)
	{
		_favorite_meal = meal;
	}
	inline void				setUnder(std::string color)
	{
		_underwear_color = color;
	}
	inline void				setDark(std::string secret)
	{
		_darkest_secret = secret;
	}
	inline void				setMonth(std::uint32_t month)
	{
		_month_of_birth = month;
	}
	inline void				setDay(std::uint32_t day)
	{
		_day_of_birth = day;
	}
	inline void				setYear(std::uint32_t year)
	{
		_year_of_birth = year;
	}
	inline std::string		&getFirstName(void)
	{
		return (_first_name);
	}
	inline std::string		&getLastName(void)
	{
		return (_last_name);
	}
	inline std::string		&getLogin(void)
	{
		return (_login);
	}
	inline std::string		&getPostal(void)
	{
		return (_postal_address);
	}
	inline std::string		&getEmail(void)
	{
		return (_email_address);
	}
	inline std::string		&getFav(void)
	{
		return (_favorite_meal);
	}
	inline std::string		&getUnder(void)
	{
		return (_underwear_color);
	}
	inline std::string		&getDarkest(void)
	{
		return (_darkest_secret);
	}
	inline std::string		&getNickName(void)
	{
		return (_nickname);
	}
	inline std::uint32_t	&getMonth(void)
	{
		return (_month_of_birth);
	}
	inline std::uint32_t	&getDay(void)
	{
		return (_day_of_birth);
	}
	inline std::uint32_t	&getYear(void)
	{
		return (_year_of_birth);
	}
	inline std::uint32_t	&getNumber(void)
	{
		return (_number);
	}


	private:

	std::string		_nickname;
	std::string		_first_name;
	std::string		_last_name;
	std::string		_login;
	std::string		_postal_address;
	std::string		_email_address;
	std::string		_favorite_meal;
	std::string		_underwear_color;
	std::string		_darkest_secret;
	std::uint32_t	_month_of_birth;
	std::uint32_t	_day_of_birth;
	std::uint32_t	_year_of_birth;
	std::uint32_t	_number;
};

#endif
