/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>  	            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:22:49 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/27 12:00:29 by hakoh	          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					eat;
	int					*status;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long				*start_simul;
	long				time_last_eat;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
	pthread_mutex_t		*output;
}				t_philo;

typedef struct s_param
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_of_meals;
	long				start_simul;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		output;
	int					death;
	int					status;
}				t_param;

/*
** param.c
*/
int			check_param(int	nb_arg, char **arg);
int			init_params(int	nb_arg, char **arg, t_param *params);
int			init_mutex(t_param *params);
void		destroy_mutex_forks(t_param *params, int nb_mutex);
void		init_philo(t_param *params, int i, int nb_philo);

/*
** death.c
*/
int			loop_nf_of_meal(t_param *params);
int			loop_if_dead(int time, t_param *params, int i);
void		*loop_death(t_param *params);

/*
** time.c
*/
long		get_time(void);
void		my_usleep(int usec, t_philo *philo);

/*
** output.c
*/
void		print_output(char *status,
				t_philo *philo, int i, unsigned long long time);
void		ft_itoa(unsigned long long n, char *str, int size, int stop);
int			ft_size_nb(unsigned long long n);

/*
** philo.c
*/
void		*loop_philo(t_philo *philo);
void		*loop_one_philo(t_philo *philo);
void		to_think(t_philo *philo);
void		to_sleep(t_philo *philo);
void		to_eat(t_philo *philo);

/*
** error.c
*/
int			print_error(int num);

/*
** utils.c
*/
int			ft_is_digit(char c);
int			ft_is_number(char *arg);
long long	ft_atoi(const char *str);
void		ft_free(void *f);

/*
** main.c
*/
void		close_simulation(int ret, t_param *params, int i);
int			run_simulation(t_param *params, int i, int ret);
int			create_thread_philo(t_param *params, int i);
void		destroy_mutex(t_param *params);

#endif