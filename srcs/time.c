/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:26:30 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/26 22:30:19 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	return (ms);
}

void	my_usleep(int usec, t_philo *philo)
{
	long	start;
	long	tot;

	start = get_time();
	tot = (long)usec + start;
	while (*philo->status == 0)
	{
		if (tot <= get_time())
			break ;
		usleep(100);
	}
}