/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:33:29 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 11:20:36 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"
#include <string.h>

int	init(t_philo *philos, t_main *m)
{
	size_t	i;

	m->stopped = 0;
	if (pthread_mutex_init(&m->mutex, NULL) != 0)
		return (0);
	i = 0;
	memset(philos, 0, m->count * sizeof(t_philo));
	while (i < m->count)
	{
		if (pthread_mutex_init(&philos[i].fork, NULL) != 0)
		{
			pthread_mutex_destroy(&m->mutex);
			return (clear_all_mutex(philos, i));
		}
		philos[i].id = i + 1;
		philos[i].main = m;
		philos[i].mutex = &m->mutex;
		philos[i].l_fork = &philos[i].fork;
		philos[i].r_fork = &philos[(i + 1) % m->count].fork;
		i++;
	}
	return (1);
}

void	clear_table(t_main *m, t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < m->threads_created)
	{
		pthread_join(philos[i].p_thread, NULL);
		i++;
	}
	i = 0;
	while (i < m->count)
	{
		pthread_mutex_destroy(&philos[i].fork);
		i++;
	}
	pthread_mutex_destroy(&m->mutex);
	free(philos);
}
