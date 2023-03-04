/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 18:19:36 by ralopez-          #+#    #+#             */
/*   Updated: 2023/01/29 18:19:37 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * free_memory:
 * This functions is called when something went wrong.
 * Desalocate all memory and display an error message.
 * 
*/
int	free_memory(t_inf *info, char *msg)
{
	int	i;

	i = -1;
	while (++i < info->n_philos)
	{
		pthread_mutex_destroy(info->forks[i]);
		free(info->forks[i]);
		if (info->philos[i] != NULL)
			free(info->philos[i]);
	}
	free(info->forks);
	free(info->philos);
	pthread_mutex_destroy(&info->mutex_print);
	pthread_mutex_destroy(&info->mutex_keep);
	pthread_mutex_destroy(&info->mutex_eat);
	return (msg_error(msg));
}

/***
 * msg_error:
 * This functions display an error message and returns -1.
 * 
*/
int	msg_error(char *msg)
{
	if (msg != NULL)
		printf("%s\n", msg);
	return (-1);
}
