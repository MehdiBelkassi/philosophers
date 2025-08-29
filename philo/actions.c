/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:50:52 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/29 16:35:42 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    think(t_philo *philo)
{
    print_status(philo, "is thinking");
}


void    ft_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep);
}
void    eat(t_philo *philo)
{
    // Correctly pick up forks to avoid a deadlock
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(philo->r_fork);
        print_status(philo, "has taken a fork");
    }
    
    // Eating
    print_status(philo, "is eating");
    
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = getcurrenttime();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    
    ft_usleep(philo->time_to_eat);
    
    // Dropping forks
    pthread_mutex_unlock(philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}
void    print_status(t_philo *philo, const char *status)
{
    pthread_mutex_lock(philo->dead_lock);
    if (*philo->dead == 1)
    {
        pthread_mutex_unlock(philo->dead_lock);
        return;
    }
    pthread_mutex_unlock(philo->dead_lock);

    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d %s\n", getcurrenttime() - philo->start_time, philo->id, status);
    pthread_mutex_unlock(philo->write_lock);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    // Add a small initial delay for even/odd philosophers to help with fork contention
    if (philo->id % 2 != 0)
        usleep(100);

    while (1)
    {
        pthread_mutex_lock(philo->dead_lock);
        if (*philo->dead == 1)
        {
            pthread_mutex_unlock(philo->dead_lock);
            break;
        }
        pthread_mutex_unlock(philo->dead_lock);

        // Your life cycle of eating, sleeping, and thinking
        eat(philo);
        ft_sleep(philo);
        think(philo);
    }
    return (NULL);
}
