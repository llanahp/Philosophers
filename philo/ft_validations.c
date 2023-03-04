/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:04:08 by ralopez-          #+#    #+#             */
/*   Updated: 2023/02/12 15:04:09 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***
 * is_digit:
 * This function verify string is compose of numbers.
 * 
 * Returns 1 if successful and 0 otherwise.
 * 
*/
int	is_digit(char *number)
{
	int	i;

	i = 0;
	while (number[i] >= '0' && number[i] <= '9')
		i++;
	if ((i > 0 && number[i] == '\0') || (number[i] >= '0' && number[i] <= '9'))
		return (1);
	else
		return (0);
}

/***
 * all_args_digit:
 * This function verify all arguments are numbers.
 * 
 * Returns 1 if successful and 0 otherwise.
 * 
*/
int	all_args_digit(t_inf *info)
{
	int	i;

	i = 0;
	while (++i < info->argc - 1)
	{
		if (is_digit(info->argv[i]) == 0)
			return (msg_error("Argument invalid"));
	}
	return (0);
}

/***
 * keep_simulation:
 * This function verify if the simulation needs to continue.
 * 
 * Returns 1 if yes and 0 otherwise.
 * 
*/
int	keep_simulation(t_inf *info)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&info->mutex_keep);
	result = info->alives;
	pthread_mutex_unlock(&info->mutex_keep);
	return (result);
}

/***
 * all_have_eat:
 * This function verify if all the philosophers had eaten.
 * 
 * Returns 1 if yes and 0 otherwise.
 * 
*/
int	all_have_eat(t_inf *info, int i, int actual)
{
	int	all_eat;

	all_eat = actual;
	pthread_mutex_lock(&info->mutex_eat);
	if (info->philos[i]->eats > 0 || info->philos[i]->eats == -1)
		all_eat = 0;
	pthread_mutex_unlock(&info->mutex_eat);
	return (all_eat);
}
