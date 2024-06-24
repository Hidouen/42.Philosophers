/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:25:02 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/12 14:21:02 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_param *params)
{
	int	i;

	i = -1;
	while (++i < params->nb_philo)
		if (pthread_mutex_destroy(&params->forks[i]) != 0)
			print_error(5);
	if (pthread_mutex_destroy(&params->output) != 0)
		print_error(5);
}

int	create_thread_philo(t_param *params, int i)
{
	if (i == -1)
	{
		if (pthread_create(&params->philo[0].thread, NULL,
				(void *)loop_one_philo, &params->philo[0]) != 0)
		{
			params->status = 1;
			print_error(3);
			return (params->philo[0].id);
		}
	}
	else
	{
		while (i < params->nb_philo)
		{
			if (pthread_create(&params->philo[i].thread, NULL,
					(void *)loop_philo, &params->philo[i]) != 0)
			{
				params->status = 1;
				print_error(3);
				return (params->philo[i].id);
			}
			i += 2;
		}
	}
	return (0);
}

int	run_simulation(t_param *params, int i, int ret)
{
	unsigned long	start;
	pthread_t		death;

	start = get_time();
	params->start_simul = start;
	if (pthread_create(&death, NULL, (void *)loop_death, params) != 0)
	{
		print_error(3);
		return (-1);
	}
	if (params->nb_philo == 1)
		ret = create_thread_philo(params, -1);
	else
	{
		ret = create_thread_philo(params, i);
		if (ret == 0)
		{
			usleep(1000);
			ret = create_thread_philo(params, 0);
		}
	}
	if (ret != 0)
		params->death = 1;
	pthread_join(death, NULL);
	return (ret);
}

void	close_simulation(int ret, t_param *params, int i)
{
	if (ret == 0)
	{
		i = -1;
		while (++i < params->nb_philo)
			pthread_join(params->philo[i].thread, NULL);
	}
	else
	{
		while (i < ret - 1)
		{
			pthread_join(params->philo[i].thread, NULL);
			i += 2;
		}
		if (ret % 2 != 0)
		{
			i = 0;
			while (i < ret - 1)
			{
				pthread_join(params->philo[i].thread, NULL);
				i += 2;
			}
		}
	}
}

int	main(int ac, char **av)
{
	t_param	params;
	int		ret;

	if (check_param(ac, av) == 0)
	{
		if (init_params(ac, av, &params) == 0)
		{
			if (params.nb_of_meals > 0)
			{
				ret = run_simulation(&params, 1, 0);
				if (ret != -1)
					close_simulation(ret, &params, 1);
			}
		}
		if (params.forks != NULL && params.philo != NULL)
			destroy_mutex(&params);
		ft_free(params.forks);
		ft_free(params.philo);
	}
	else
		return (1);
	return (0);
}