/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:57 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 11:16:46 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long long	get_timestamp(void)
{
	long long		time_ms;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	return (time_ms);
}

void	p_usleep(t_philo *philo, long long ms)
{
	long long	time_till;
	long long	counter;

	time_till = get_timestamp() + ms;
	counter = 0;
	while (get_timestamp() < time_till)
	{
		usleep(250);
		if (counter > 1000)
		{
			if (stop_dinning(philo))
				break ;
			counter = 0;
		}
		counter++;
	}
}

void	ft_usleep(long long ms)
{
	long long	time_till;
	long long	counter;

	time_till = get_timestamp() + ms;
	counter = 0;
	while (get_timestamp() < time_till)
	{
		usleep(250);
		if (counter > 1000)
		{
			counter = 0;
		}
		counter++;
	}
}

int	philo_threads(t_main *m, t_philo *philos)
{
	m->threads_created = 0;
	while (m->threads_created < m->count)
	{
		if (pthread_create(&philos[m->threads_created].p_thread, NULL, p_dine,
				&philos[m->threads_created]) != 0)
		{
			pthread_mutex_lock(&m->mutex);
			m->stopped = 1;
			printf("Error creating threads!\n");
			pthread_mutex_unlock(&m->mutex);
			return (0);
		}
		m->threads_created++;
	}
	return (1);
}

int	philo_run(t_main *m)
{
	t_philo	*philos;
	int		ret;

	philos = malloc(m->count * sizeof(t_philo));
	if (!philos || !init(philos, m))
	{
		free(philos);
		return (0);
	}
	ret = philo_threads(m, philos);
	while (ret && monitor(m, philos))
		ft_usleep(1);
	clear_table(m, philos);
	return (ret);
}
