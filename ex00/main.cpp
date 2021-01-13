/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 23:40:06 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/12 00:14:08 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <cctype>

int		main(int argc, char **argv)
{
	std::string		arg;

	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else for (int i = 1; i < argc; i++)
	{
		arg = argv[i];
		for (std::string::iterator it = arg.begin(); it != arg.end(); it++)
			std::cout << (char)(*it - 32 * std::islower(*it));
	}
	std::cout << std::endl;
	return (0);
}
