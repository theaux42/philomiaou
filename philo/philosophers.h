/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:09:48 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 11:20:33 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct t_main
{
	int					stopped;
	size_t				threads_created;
	size_t				count;
	size_t				meals_limit;
	long long			time_to_die;
	long long			time_to_start;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	pthread_mutex_t		mutex;
	t_philo				*philo;
}						t_main;

typedef struct s_philo
{
	size_t				id;
	size_t				total_meals;
	long long			last_meat;
	pthread_mutex_t		*mutex;
	pthread_mutex_t		fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			p_thread;
	struct t_main		*main;
}						t_philo;

int						philo_run(t_main *m);
int						stop_dinning(t_philo *philo);
int						monitor(t_main *m, t_philo *philos);
// init functions
int						init(t_philo *philos, t_main *m);
void					clear_table(t_main *m, t_philo *philos);

// utils functions
size_t					ft_atoi(const char *s, int *error);
int						clear_all_mutex(t_philo *philos, int i);
void					print_message(t_philo *philo, char *action);

// time functions
long long				get_timestamp(void);
void					p_usleep(t_philo *philo, long long ms);
void					ft_usleep(long long ms);

// functions for actions of the philosophers
void					p_sleep(t_philo *philo);
void					p_think(t_philo *philo);
void					p_eat(t_philo *philo);
void					p_forks(t_philo *philo);
void					*p_dine(void *philo_ptr);
void					*single_philo(t_philo *philo);

#endif