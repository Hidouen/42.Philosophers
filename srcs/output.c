/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:32:11 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/26 22:05:49 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_size_nb(unsigned long long n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

void	ft_itoa(unsigned long long n, char *str, int size, int stop)
{
	while (size > stop)
	{
		str[--size] = (n % 10) + 48;
		n /= 10;
	}
}

void	print_output(
		char *status, t_philo *philo, int i, unsigned long long time)
{
	static char			output[254];
	int					size_time;
	int					size_id;

	size_time = ft_size_nb(time);
	ft_itoa(time, output, size_time, 0);
	output[size_time++] = ' ';
	size_id = ft_size_nb((unsigned long long)philo->id);
	ft_itoa((unsigned long long)philo->id,
		output, size_id + size_time, size_time);
	size_id += size_time;
	while (status[++i] != '\0')
	{
		output[size_id] = status[i];
		size_id++;
	}
	output[size_id] = '\0';
	if (*philo->status == 0)
		write(1, output, size_id);
}