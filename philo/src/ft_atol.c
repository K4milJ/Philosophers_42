/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:01:34 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/23 14:42:42 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only positive values");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit");
	return (number);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}
