/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:39:25 by hakoh             #+#    #+#             */
/*   Updated: 2022/08/12 14:12:00 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int num)
{
	if (num == 1)
		write(2, "Error: too many arguments or too few arguments\n", 47);
	if (num == 2)
		write(2, "Error: bad argument\n", 20);
	if (num == 3)
		write(2, "Error: thread not created\n", 26);
	if (num == 4)
		write(2, "Error: mutex not inited\n", 24);
	if (num == 5)
		write(2, "Error: mutex not destroyed\n", 27 );
	return (1);
}