/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:35:36 by ralopez-          #+#    #+#             */
/*   Updated: 2023/01/27 12:35:38 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define INVALID_INPUT "Invalid input.\nExample: \n\t./philo 5 20 10 5"
# define MSG1 " has taken a fork"
# define MSG2 " is eating"
# define MSG3 " is sleeping"
# define MSG4 " is thinking"
# define MSG5 " died"

typedef struct s_inf	t_inf;

typedef struct s_philo
{
	int			eats;
	int			eating;
	int			id;
	t_inf		*info;
	int			l_fork;
	int			r_fork;
	pthread_t	thread;
	long		last_eat;
}		t_philo;

typedef struct s_inf
{
	char			**argv;
	int				argc;
	int				n_philos;
	long			time_eat;
	int				time_to_die;
	int				time_sleep;
	pthread_mutex_t	**forks;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_keep;
	pthread_mutex_t	mutex_eat;
	pthread_t		simultion;
	t_philo			**philos;
	long			time_start;
	int				alives;
	int				keep_going;
	int				n_eat;
}		t_inf;

/*** ft_atoi.c */
int		ft_atoi(const char *str);

/** ft_error.c */
int		free_memory(t_inf *info, char *msg);
int		msg_error(char *msg);

/*** ft_init.c */
int		alloc_mutex_fork(t_inf *info);
int		init_mutex(t_inf *info);
void	set_forks(t_philo *philo);
int		create_philos(t_inf *info);
int		init_structure(t_inf *info);

/*** ft_main.c */
void	*start_simulation(void *info);
void	*end_simulation(t_inf *info, int i);

/***   philo.c*/
void	eat_philo(t_philo **philo);
void	sleep_philo(t_philo **philo);
void	*start_philo(void *info);

/*** ft_print.c */
long	get_time(void);
long	get_elapsed_time(t_inf *info);
void	print(t_inf *info, int id, char *msg);
void	print_dead(t_inf *info, int id, char *msg);

/*** ft_validations.c */
int		is_digit(char *number);
int		all_args_digit(t_inf *info);
int		keep_simulation(t_inf *info);
int		all_have_eat(t_inf *info, int i, int actual);

#endif