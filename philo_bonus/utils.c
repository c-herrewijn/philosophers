/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cherrewi <cherrewi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 17:58:18 by cherrewi      #+#    #+#                 */
/*   Updated: 2023/08/02 13:56:28 by cherrewi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/*
Atoi = Array To Integer
Parses a string with digits to an int.
The first char can be a + or - sign.
Leading white spaces are skipped.
*/
int	ft_atoi(const char *str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((int)(*str)))
		{
			break ;
		}
		num = num * 10;
		num = num + ((*str) - 48);
		str++;
	}
	return ((sign) * (num));
}

/*
check if string has format:
optionally starts with a plus '+' or minus '-' sign
only consists of digits [0-9]
is within range [INT_MIN, INT_MAX]
*/
bool	ft_isinteger(char *int_str)
{
	int			i;
	int			sign;
	long int	num;

	if (int_str == NULL || int_str[0] == '\0')
		return (false);
	i = 0;
	sign = 1;
	if (int_str[0] == '-')
		sign = -1;
	if (int_str[0] == '-' || int_str[0] == '+')
		i++;
	num = 0;
	while (int_str[i] != '\0')
	{
		if (ft_isdigit(int_str[i]) == false)
			return (false);
		num = num * 10;
		num = num + (int_str[i] - 48);
		i++;
	}
	num = num * sign;
	return (num >= INT_MIN && num <= INT_MAX);
}

/*
check if string has format:
optionally starts with a plus '+' or minus '-' sign
only consists of digits [0-9]
is within range [1, INT_MAX]
*/
bool	ft_is_pos_integer(char *int_str)
{
	return (ft_isinteger(int_str) && ft_atoi(int_str) > 0);
}
