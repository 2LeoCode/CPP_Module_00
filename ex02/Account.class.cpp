/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:36:51 by lsuardi           #+#    #+#             */
/*   Updated: 2021/01/16 15:15:38 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.class.hpp"
#include <fstream>
#include <sstream>
#include <ctime>

int					Account::_nbAccounts = 0, Account::_totalAmount = 0, Account::_totalNbDeposits = 0, Account::_totalNbWithdrawals = 0;

std::string			getTimestamp(void)
{
	std::tm				tm;
	std::time_t			time = std::time(NULL);
	std::istringstream	c_time(std::ctime(&time));
	std::ostringstream	formatted_c_time;

	c_time >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
	formatted_c_time << std::put_time(&tm, "%Y%m%d_%H%M%S");
	return (formatted_c_time.str());
}

static std::string	begin_timestamp = getTimestamp();

void				Account::_displayTimestamp( void )
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	out << '[' << getTimestamp() << "] ";
	out.close();
}

Account::Account(int initial_deposit) : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0), _checkAmountCount(0)
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_nbAccounts++;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	out << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl;
	out.close();
}

Account::~Account(void)
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_nbAccounts--;
	_totalAmount -= _amount;
	_displayTimestamp();
	out << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
	out.close();
}

int					Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int					Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int					Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int					Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

void				Account::displayAccountsInfos(void)
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_displayTimestamp();
	out << "accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
	out.close();
}

void				Account::makeDeposit(int deposit)
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_displayTimestamp();
	_nbDeposits++;
	out << "index:" << _accountIndex << ";p_amount:" << _amount << ";deposit:" << deposit << ";amount:" << _amount + deposit << ";nb_deposits:" << _nbDeposits << std::endl;
	_amount += deposit;
	_totalAmount += deposit;
	_totalNbDeposits++;
	out.close();
}

bool				Account::makeWithdrawal(int withdrawal)
{
	bool			ret;
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_displayTimestamp();
	out << "index:" << _accountIndex << ";p_amount:" << _amount << ";withdrawal:";
	_amount -= withdrawal;
	if ((ret = checkAmount()))
	{
		_nbWithdrawals++;
		_totalNbWithdrawals++;
		_totalAmount -= withdrawal;
		out << withdrawal << ";amount:" << _amount << ";nb_withdrawals:" << _nbWithdrawals;
	}
	else
	{
		_amount += withdrawal;
		out << "refused";
	}
	out << std::endl;
	return (ret);
}

int					Account::checkAmount( void ) const
{
	_checkAmountCount++;
	return (_amount >= 0);
}

void				Account::displayStatus( void ) const
{
	std::ofstream	out(begin_timestamp + ".log", std::ios::out | std::ios::app);

	_displayTimestamp();
	out << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
	out.close();
}
