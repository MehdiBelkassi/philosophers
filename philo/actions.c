/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:50:52 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/28 16:19:26 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    think(t_philo *philo)
{
    printf("%d is thinking",philo->id);
}


void    ft_sleep(t_philo *philo)
{
    if (ft_usleep(philo->time_to_sleep) == 0)
        printf("%d is sleeping",philo->id);
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(philo->r_fork);
    printf("%d has taken a fork",philo->id);
    pthread_mutex_lock(philo->l_fork);
    printf("%d has taken a fork",philo->id);
    printf("%d is eating",philo->id);
    ft_usleep(philo->time_to_eat);
    philo->last_meal = getcurrenttime();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (!philo->dead)
    {
        eat(philo);
        ft_sleep(philo);
        think(philo);
        // puts("hi");
    }
    return (NULL);
}