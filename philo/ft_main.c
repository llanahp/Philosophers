/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 12:33:49 by ralopez-          #+#    #+#             */
/*   Updated: 2023/02/26 12:33:50 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * start_simulation:
 * This function is called when the simulation need to stops.
 * 
 */
void	*end_simulation(t_inf *info, int i)
{
	int	j;

	j = -1;
	pthread_mutex_lock(&info->mutex_keep);
	info->alives = 0;
	pthread_mutex_unlock(&info->mutex_keep);
	pthread_mutex_lock(&info->mutex_print);
	if (i != -1)
		print_dead(info, i + 1, MSG5);
	while (++j < info->n_philos)
		pthread_detach(info->philos[j]->thread);
	return ((void *) 0);
}

/***
 * start_simulation:
 * This function is called to continuously check if any philosopher has died 
 *  or if everyone has eaten the indicated number of times.
 * 
 */
void	*start_simulation(void *infos)
{
	t_inf	*info;
	int		i;
	int		all_eat;
	long	time;

	info = (t_inf *)infos;
	while (keep_simulation(info))
	{
		all_eat = 1;
		i = -1;
		while (++i < info->n_philos)
		{
			pthread_mutex_lock(&info->mutex_eat);
			time = (get_time() - info->philos[i]->last_eat);
			if ((time >= info->time_to_die) && info->philos[i]->eating == 0
				&& (info->philos[i]->eats > 0 || info->philos[i]->eats == -1))
				pthread_exit(end_simulation(info, i));
			pthread_mutex_unlock(&info->mutex_eat);
			all_eat = all_have_eat(info, i, all_eat);
		}
		if (all_eat == 1)
			end_simulation(info, -1);
	}
	pthread_exit((void *)0);
}

/***
 * throw_pthreads:
 * This function creates a thread for each philosopher.
 * Also create one to control all of ones.
 * 
 * Returns -1 if something went wrong.
 * 
 */
int	throw_pthreads(t_inf *info)
{
	if (create_philos(info) == -1)
		return (-1);
	if (pthread_create(&info->simultion, NULL, start_simulation, info) != 0)
		return (free_memory(info, "mutex init failed"));
	return (1);
}

/***
 * main:
 * This function is the main function of the program.
 * 
 * Initialize all philosophers and run the simulation.
 * 
 */
int	main(int argc, char **argv)
{
	t_inf	info;

	if (argc != 5 && argc != 6)
	{
		printf(INVALID_INPUT);
		return (0);
	}
	info.argc = argc;
	info.argv = argv;
	if (init_structure(&info) == -1)
		return (-1);
	if (throw_pthreads(&info) == -1)
		return (-1);
	pthread_join(info.simultion, NULL);
	free_memory(&info, NULL);
	return (0);
}
