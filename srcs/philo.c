/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 12:03:01 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/27 11:35:11 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(philo->output);
	print_output(" has taken a fork\n", philo, -1,
		get_time() - *philo->start_simul);
	print_output(" has taken a fork\n", philo, -1,
		get_time() - *philo->start_simul);
	pthread_mutex_unlock(philo->output);
	philo->time_last_eat = get_time() - *philo->start_simul;
	pthread_mutex_lock(philo->output);
	print_output(" is eating\n", philo, -1,
		get_time() - *philo->start_simul);
	philo->eat = 1;
	pthread_mutex_unlock(philo->output);
	philo->nb_of_meals--;
	if (philo->nb_of_meals <= 0)
		philo->nb_of_meals = 0;
	my_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	philo->eat = 0;
}

void	to_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	print_output(" is sleeping\n", philo, -1,
		get_time() - *philo->start_simul);
	pthread_mutex_unlock(philo->output);
	my_usleep(philo->time_to_sleep, philo);
}

void	to_think(t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	print_output(" is thinking\n", philo, -1,
		get_time() - *philo->start_simul);
	pthread_mutex_unlock(philo->output);
}

void	*loop_philo(t_philo *philo)
{
	while (*philo->status == 0)
	{
		to_eat(philo);
		to_sleep(philo);
		to_think(philo);
		usleep(100);
	}
	return (NULL);
}

void	*loop_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->output);
	print_output(" has taken a fork\n", philo, -1,
		get_time() - *philo->start_simul);
	pthread_mutex_unlock(philo->output);
	while (*philo->status != 1)
		usleep(100);
	pthread_mutex_unlock(philo->first_fork);
	return (NULL);
}