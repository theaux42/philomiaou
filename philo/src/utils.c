/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:34:18 by tbabou            #+#    #+#             */
/*   Updated: 2024/09/09 11:18:30 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	is_valid(const char *s)
{
	if (*s == '\0')
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

size_t	ft_atoi(const char *s, int *error)
{
	size_t	res;
	size_t	tmp;

	res = 0;
	if (*error == 1)
		return (0);
	if (!is_valid(s))
	{
		*error = 1;
		return (0);
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		tmp = res;
		res = res * 10 + (*s - '0');
		if (res < tmp)
		{
			*error = 1;
			return (0);
		}
		s++;
	}
	return (res);
}

void	print_message(t_philo *philo, char *action)
{
	pthread_mutex_lock(philo->mutex);
	if (!philo->main->stopped)
		printf("%lld %zu %s\n", get_timestamp() - philo->main->time_to_start,
			philo->id, action);
	pthread_mutex_unlock(philo->mutex);
}

void	*single_philo(t_philo *philo)
{
	print_message(philo, "has taken a fork");
	p_usleep(philo, philo->main->time_to_die);
	print_message(philo, "is dead");
	pthread_mutex_lock(philo->mutex);
	philo->main->stopped = 1;
	pthread_mutex_unlock(philo->mutex);
	return (NULL);
}

int	clear_all_mutex(t_philo *philos, int i)
{
	while (i-- > 0)
		pthread_mutex_destroy(&philos[i].fork);
	return (0);
}
