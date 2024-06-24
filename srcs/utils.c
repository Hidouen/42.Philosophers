/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:40:22 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/30 10:47:16 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (0);
	return (1);
}

int	ft_is_number(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_is_digit(arg[i]) != 0)
			return (1);
		i++;
	}
	if (ft_atoi(arg) > INT_MAX)
		return (1);
	return (0);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			s;
	long long	res;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	s = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * s);
}

void	ft_free(void *f)
{
	if (f != NULL)
	{
		free(f);
		f = NULL;
	}
}