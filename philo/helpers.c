/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:38:29 by mbelkass          #+#    #+#             */
/*   Updated: 2025/09/09 23:12:11 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

int	ft_usleep(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = getcurrenttime();
	while ((getcurrenttime() - start) < milliseconds)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == 1)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);
		usleep(500);
	}
	return (0);
}

size_t	getcurrenttime(void)
{
	struct timeval	ap;

	if (gettimeofday(&ap, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((ap.tv_sec * 1000) + (ap.tv_usec / 1000));
}

void	one_philo(t_philo *philo)
{
	think(philo);
	print_status(philo, "has taken a fork");
	ft_usleep(philo, philo->time_to_die);
}
