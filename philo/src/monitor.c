/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:10:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 11:23:47 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	stop_dinning(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(philo->mutex);
	ret = philo->main->stopped;
	pthread_mutex_unlock(philo->mutex);
	return (ret);
}

static int	has_died(t_philo *philo)
{
	long long	delta;
	long long	ms;

	if (philo->last_meat <= 0)
		return (0);
	ms = get_timestamp();
	delta = ms - philo->last_meat;
	if (delta < philo->main->time_to_die)
		return (0);
	philo->main->stopped = 1;
	printf("%lld %zu died\n", ms - philo->main->time_to_start, philo->id);
	return (1);
}

static int	max_meals_reached(t_main *m, t_philo *philos)
{
	size_t	i;
	size_t	limit_reached;

	i = 0;
	limit_reached = 0;
	while (i < m->count)
	{
		pthread_mutex_lock(&m->mutex);
		if (philos[i].total_meals >= m->meals_limit)
			limit_reached++;
		pthread_mutex_unlock(&m->mutex);
		i++;
	}
	if (limit_reached == m->count)
	{
		pthread_mutex_lock(&m->mutex);
		printf("All philosophers ate %zu times\n", m->meals_limit);
		m->stopped = 1;
		pthread_mutex_unlock(&m->mutex);
		return (1);
	}
	return (0);
}

int	monitor(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->count)
	{
		pthread_mutex_lock(&m->mutex);
		if (m->stopped || has_died(&philos[i]))
		{
			pthread_mutex_unlock(&m->mutex);
			return (0);
		}
		pthread_mutex_unlock(&m->mutex);
		i++;
	}
	if (m->meals_limit > 0 && max_meals_reached(m, philos))
		return (0);
	return (1);
}
