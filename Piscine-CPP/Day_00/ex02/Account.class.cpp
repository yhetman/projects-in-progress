/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhetman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:23:25 by yhetman           #+#    #+#             */
/*   Updated: 2019/12/03 20:36:54 by yhetman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include "Account.class.hpp"

typedef struct tm	t_manager;

int			Account::_nbAccounts(0);
int			Account::_totalAmount(0);
int			Account::_totalNbDeposits(0);
int			Account::_totalNbWithdrawals(0);


int			Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int			Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int			Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int			Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}


Account::Account(int initial_deposit) : 
		_nbCountAmountCalls(0),
		_accountIndex(_nbAccounts++),
		_amount(initial_deposit),
		_nbDeposits(0),
		_nbWithdrawals(0)
{
	_totalAmount += initial_deposit;

	Account::_displayTimestamp();

	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << initial_deposit;
	std::cout << ";created" << std::endl;
}


Account::~Account(void)
{
	_nbAccounts--;

	Account::_displayTimestamp();

	std::cout << "index:" << _nbAccounts;
	std::cout << ";amount:" << _amount;
	std::cout << ";closed" << std::endl;
}


int			Account::checkAmount( void ) const
{
	_nbCountAmountCalls++;

	return (_amount);
}


void		Account::_displayTimestamp( void )
{
	time_t		rawtime;
	t_manager	*timeinfo;
	char		buffer[25];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 25, "[%Y%m%d_%H%M%S] ", timeinfo);

	std::cout << buffer;
}


void		Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();

	std::cout << "accounts:" << _nbAccounts;
	std::cout << ";total:" << _totalAmount;
	std::cout << ";deposits:" << _totalNbDeposits;
	std::cout << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}


void		Account::makeDeposit( int deposit )
{
	Account::_displayTimestamp();

	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << _amount;
	std::cout << ";deposit:" << deposit;

	_amount += deposit;
	_nbDeposits++;
	_totalAmount += deposit;
	_totalNbDeposits++;

	std::cout << ";amount:" << _amount;
	std::cout << ";nb_deposits:" << _nbDeposits << std::endl;
}


bool		Account::makeWithdrawal( int withdrawal )
{
	Account::_displayTimestamp();

	std::cout << "index:" << _accountIndex;
	std::cout << ";p_amount:" << _amount;
	std::cout << ";withdrawal:";

	if (_amount < withdrawal)
	{
		std::cout << "refused" << std::endl;
		return (false);
	}
	else
	{
		_amount -= withdrawal;
		_nbWithdrawals++;
		_totalAmount -= withdrawal;
		_totalNbWithdrawals++;
	}

	std::cout << withdrawal << ";amount:" << _amount;
	std::cout << ";nb_withdrawals:" << 1 << std::endl;

	return (true);
}

void		Account::displayStatus( void ) const
{
	Account::_displayTimestamp();

	std::cout << "index:" << _accountIndex;
	std::cout << ";amount:" << _amount;
	std::cout << ";deposits:" << _nbDeposits;
	std::cout << ";withdrawals:" << _nbWithdrawals << std::endl;
}
