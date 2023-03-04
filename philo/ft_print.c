/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:11:01 by ralopez-          #+#    #+#             */
/*   Updated: 2023/01/29 15:11:03 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * get_time:
 * This function returns the current time in miliseconds.
 *  
 */
long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

/***
 * get_elapsed_time:
 * This function returns the elapsed between two points in time.
 *  
 */
long	get_elapsed_time(t_inf *info)
{
	return (get_time() - info->time_start);
}

/***
 * print:
 * This function display a message in console.
 *  
 */
void	print(t_inf *info, int id, char *msg)
{
	pthread_mutex_lock(&info->mutex_print);
	if (keep_simulation(info))
	{
		printf("%ld %d", get_elapsed_time(info), id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&info->mutex_print);
}

/***
 * print_dead:
 * This function display a message in console.
 * Indicates one philosopher is dead.
 * 
 */
void	print_dead(t_inf *info, int id, char *msg)
{
	printf("%ld %d", get_elapsed_time(info), id);
	printf("%s\n", msg);
}
