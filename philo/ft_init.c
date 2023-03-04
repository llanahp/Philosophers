/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:29:18 by ralopez-          #+#    #+#             */
/*   Updated: 2023/01/27 15:29:19 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * alloc_mutex_fork:
 * This function allocate space for all forks.
 * 
 * Returns 0 if successful and -1 otherwise.
 * 
 */
int	alloc_mutex_fork(t_inf *info)
{
	int	i;
	int	size;

	i = -1;
	size = info->n_philos + 1;
	info->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * size);
	if (!info->forks)
		return (msg_error("Error in malloc"));
	while (++i < info->n_philos)
	{
		info->forks[i] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		if (!info->forks[i])
		{
			while (--i > 0)
				free(info->forks[i]);
			free(info->forks);
			return (msg_error("Error in malloc"));
		}
	}
	info->forks[i] = NULL;
	return (0);
}

/***
 * init_mutex:
 * This function initialize the mutex for all the forks.
 * 
 * Returns 0 if successful and -1 otherwise.
 * 
 */
int	init_mutex(t_inf *info)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
	{
		if (pthread_mutex_init(info->forks[i], NULL) != 0)
		{
			while (--i > 0)
			{
				pthread_mutex_destroy(info->forks[i]);
				free(info->forks[i]);
			}
			free(info->forks);
			info->forks = NULL;
			return (msg_error("mutex init failed"));
		}
	}
	return (0);
}

/***
 * set_forks:
 * This function defines for a philosopher which forks he is able to take.
 *  
 */
void	set_forks(t_philo *philo)
{
	philo->l_fork = philo->id;
	philo->r_fork = philo->id + 1;
	if (philo->r_fork >= philo->info->n_philos)
		philo->r_fork = 0;
}

/***
 * create_philos:
 * This function initializes an array of t_philo structures for each philosopher
 * 	,creates a new thread for each philosopher, and sets various
 * 	fields for each philosopher.
 * 
 * It returns 0 if successful and -1 otherwise.
 * 
 * The function sets the left and right forks of each philosopher using 
 *  set_forks() and passes the start_execution() function as an argument 
 * 	to pthread_create(), which is the starting function for the thread that 
 *  executes the philosopher's actions.
 *  
 */
int	create_philos(t_inf *info)
{
	int	i;

	i = -1;
	info->philos = malloc(sizeof(t_philo) * info->n_philos);
	if (!info->philos)
		return (msg_error("Error malloc"));
	info->time_start = get_time();
	while (++i < info->n_philos)
	{
		info->philos[i] = malloc(sizeof(t_philo) * 1);
		if (!info->philos)
			return (msg_error("Error malloc"));
		info->philos[i]->id = i;
		info->philos[i]->eating = 0;
		info->philos[i]->eats = info->n_eat;
		info->philos[i]->info = info;
		info->philos[i]->last_eat = info->time_start;
		set_forks(info->philos[i]);
		if (pthread_create(&info->philos[i]->thread, NULL,
				start_philo, &info->philos[i]) != 0)
			return (msg_error("Error create pthread"));
	}
	return (0);
}

/***
 * init_structure:
 * This function initializes the info structure based on the command-line 
 * 	arguments passed to the program, sets various timing values,
 * 	and initializes mutex variables.
 * 
 * It returns -1 if there is an error in initialization and 1 otherwise.
 * 
 * The function also checks if the n_eat variable is set to a 
 * 	positive value if the program is run with six arguments.
 *  
 */
int	init_structure(t_inf *info)
{
	if (all_args_digit(info) == -1)
		return (-1);
	info->n_eat = -1;
	if (info->argc == 6)
		info->n_eat = ft_atoi(info->argv[5]);
	if (info->argc == 6 && info->n_eat <= 0)
		return (-1);
	info->n_philos = ft_atoi(info->argv[1]);
	info->keep_going = 1;
	if (alloc_mutex_fork(info) == -1 || init_mutex(info) == -1)
		return (-1);
	if (pthread_mutex_init(&info->mutex_print, NULL) != 0)
		return (free_memory(info, "mutex init failed"));
	if (pthread_mutex_init(&info->mutex_keep, NULL) != 0)
		return (free_memory(info, "mutex init failed"));
	if (pthread_mutex_init(&info->mutex_eat, NULL) != 0)
		return (free_memory(info, "mutex init failed"));
	info->alives = 1;
	info->time_to_die = ft_atoi(info->argv[2]);
	info->time_eat = ft_atoi(info->argv[3]);
	info->time_sleep = ft_atoi(info->argv[4]);
	return (1);
}
