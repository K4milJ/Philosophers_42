#include "../include/philo.h"

static bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char *valid_input(const char *str)
{
	int len;			// length of the string
	const char *number;	// pointer to the numeric part

	len = 0;

	// 1) Skip spaces
	while (is_space(*str))
		++str;

	// 2) Skip '+' but reject '-'
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive values");

	// 3) Ensure first character is a digit
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");

	number = str;

	// 4) Count digits
	while (is_digit(*str++))
		++len;

		// 5) Limit to 10 digits
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
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit");
	return (num);
}