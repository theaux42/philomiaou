/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:05:47 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 01:51:34 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	p_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
}

void	p_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	p_usleep(philo, philo->main->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	p_eat(t_philo *philo)
{
	p_forks(philo);
	pthread_mutex_lock(philo->mutex);
	philo->total_meals++;
	philo->last_meat = get_timestamp();
	pthread_mutex_unlock(philo->mutex);
	print_message(philo, "is eating");
	p_usleep(philo, philo->main->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*p_dine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->main->count == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(philo->main->time_to_sleep);
	while (!stop_dinning(philo))
	{
		p_eat(philo);
		if (stop_dinning(philo))
			break ;
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}
