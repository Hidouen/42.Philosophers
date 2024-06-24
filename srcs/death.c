/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:18:07 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/27 11:59:43 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loop_nb_of_meal(t_param *params)
{
	int	i;

	i = -1;
	while (++i < params->nb_philo)
	{
		if (params->philo[i].nb_of_meals > 0)
			return (0);
		usleep(100);
	}
	if (i == params->nb_philo)
	{
		params->death = 1;
		pthread_mutex_lock(&params->output);
		params->status = 1;
		pthread_mutex_unlock(&params->output);
	}
	return (1);
}

int	loop_if_dead(int time, t_param *params, int i)
{
	if (time >= params->time_to_die && params->philo[i].eat == 0)
	{
		params->death = 1;
		pthread_mutex_lock(&params->output);
		params->status = 1;
		printf("%ld %d died\n", time
			+ params->philo[i].time_last_eat, params->philo[i].id);
		pthread_mutex_unlock(&params->output);
		return (1);
	}
	return (0);
}

void	*loop_death(t_param *params)
{
	int	i;
	int	time;

	while (params->death == 0)
	{
		i = -1;
		while (++i < params->nb_philo)
		{
			time = get_time() - params->start_simul
				- params->philo[i].time_last_eat;
			if (loop_if_dead(time, params, i) == 1)
				return (NULL);
			usleep(100);
		}
		if (loop_nb_of_meal(params) == 1)
			break ;
	}
	return (NULL);
}