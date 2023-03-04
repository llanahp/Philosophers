/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:35:31 by ralopez-          #+#    #+#             */
/*   Updated: 2023/01/27 12:35:32 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * eat_philo:
 *  This function is in charge of the eating routine.
 * 
*/
void	eat_philo(t_philo **philo)
{
	long	start;

	if (keep_simulation((*philo)->info))
		pthread_mutex_lock((*philo)->info->forks[(*philo)->l_fork]);
	print((*philo)->info, (*philo)->id, MSG1);
	if (keep_simulation((*philo)->info))
		pthread_mutex_lock((*philo)->info->forks[(*philo)->r_fork]);
	(*philo)->eating = 1;
	print((*philo)->info, (*philo)->id, MSG1);
	pthread_mutex_lock(&(*philo)->info->mutex_eat);
	(*philo)->last_eat = get_time();
	pthread_mutex_unlock(&(*philo)->info->mutex_eat);
	print((*philo)->info, (*philo)->id, MSG2);
	start = get_time();
	while (keep_simulation((*philo)->info)
		&& (get_time() - start) < (*philo)->info->time_eat)
		usleep(0);
	if (keep_simulation((*philo)->info))
	{
		(*philo)->eating = 0;
		pthread_mutex_unlock((*philo)->info->forks[(*philo)->l_fork]);
		pthread_mutex_unlock((*philo)->info->forks[(*philo)->r_fork]);
	}
}

/***
 * sleep_philo:
 *  This function is in charge of the sleeping routine.
 * 
*/
void	sleep_philo(t_philo **philo)
{
	long	start;

	if (keep_simulation((*philo)->info))
		print((*philo)->info, (*philo)->id, MSG3);
	start = get_time();
	while ((keep_simulation((*philo)->info))
		&& (get_time() - start) < (*philo)->info->time_sleep)
		usleep(0);
}

/***
 * start_philo:
 *  This function is in charge of the philosopher's life cycle.
 * 
*/
void	*start_philo(void *info)
{
	t_philo	**philo;

	philo = (t_philo **)info;
	if ((*philo)->id % 2 == 0 && (*philo)->info->n_philos > 1)
		usleep((*philo)->info->time_eat);
	while (keep_simulation((*philo)->info))
	{
		eat_philo(philo);
		pthread_mutex_lock(&(*philo)->info->mutex_eat);
		if ((*philo)->eats != 0 && (*philo)->eats != -1)
			(*philo)->eats = (*philo)->eats - 1;
		pthread_mutex_unlock(&(*philo)->info->mutex_eat);
		if (keep_simulation((*philo)->info))
			sleep_philo(philo);
		if (keep_simulation((*philo)->info))
			print((*philo)->info, (*philo)->id, MSG4);
	}
	pthread_exit((void *)0);
}
