/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:37:04 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/27 12:05:35 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_param *params, int i, int nb_philo)
{
	while (++i < nb_philo)
	{
		params->philo[i].id = i + 1;
		if (params->philo[i].id % 2 == 0 || params->philo[i].id == nb_philo)
		{
			params->philo[i].first_fork = &params->forks[i];
			if (nb_philo != 1)
				params->philo[i].second_fork = &params->forks[i - 1];
		}
		else
		{
			params->philo[i].first_fork = &params->forks[i - 1];
			if (i == 0)
				params->philo[i].first_fork = &params->forks[nb_philo - 1];
			params->philo[i].second_fork = &params->forks[i];
		}
		params->philo[i].output = &params->output;
		params->philo[i].time_to_eat = params->time_to_eat;
		params->philo[i].time_to_sleep = params->time_to_sleep;
		params->philo[i].nb_of_meals = params->nb_of_meals;
		params->philo[i].time_last_eat = 0;
		params->philo[i].status = &params->status;
		params->philo[i].start_simul = &params->start_simul;
		params->philo[i].eat = 0;
	}
}

void	destroy_mutex_forks(t_param *params, int nb_mutex)
{
	int	i;

	i = -1;
	while (++i < nb_mutex)
		if (pthread_mutex_destroy(&params->forks[i]) != 0)
			print_error(5);
}

int	init_mutex(t_param *params)
{
	int	i;

	i = -1;
	while (++i < params->nb_philo)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			print_error(4);
			destroy_mutex_forks(params, i);
			return (1);
		}
	}
	if (pthread_mutex_init(&params->output, NULL) != 0)
	{
		print_error(4);
		destroy_mutex_forks(params, i);
		return (1);
	}
	return (0);
}

int	init_params(int nb_arg, char **arg, t_param *params)
{
	params->nb_philo = ft_atoi(arg[1]);
	params->time_to_die = ft_atoi(arg[2]);
	params->time_to_eat = ft_atoi(arg[3]);
	params->time_to_sleep = ft_atoi(arg[4]);
	params->start_simul = 0;
	params->status = 0;
	params->death = 0;
	if (nb_arg == 6)
		params->nb_of_meals = ft_atoi(arg[5]);
	else
		params->nb_of_meals = INT_MAX;
	params->philo = NULL;
	params->forks = NULL;
	params->forks = malloc(sizeof(pthread_mutex_t) * params->nb_philo);
	if (params->forks == NULL)
		return (1);
	if (init_mutex(params) != 0)
		return (1);
	params->philo = malloc(sizeof(t_philo) * params->nb_philo);
	if (params->philo == NULL)
		return (1);
	init_philo(params, -1, params->nb_philo);
	return (0);
}

int	check_param(int nb_arg, char **arg)
{
	int		i;

	i = 0;
	if (nb_arg > 6 || nb_arg < 5)
		return (print_error(1));
	while (++i < nb_arg)
	{
		if (ft_is_number(arg[i]) != 0)
			return (print_error(2));
	}
	return (0);
}