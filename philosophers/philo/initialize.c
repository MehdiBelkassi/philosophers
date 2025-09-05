/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:51:25 by mbelkass          #+#    #+#             */
/*   Updated: 2025/09/05 18:50:42 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void     init1_helper(t_program *program, int numb_of_philos)
{
    int i;

    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    i = 0;
    while (i < numb_of_philos)
    {
        pthread_mutex_init(&program->forks[i], NULL);
        i++;
    }
}

int    init1(t_program *program, int *numbers)
{
    int numb_of_philos;
    int i;

    numb_of_philos = numbers[0];
    program->philos = malloc(sizeof(t_philo) * (numb_of_philos + 1));
    if (!program->philos)
        return 1;
    program->forks = malloc(sizeof(pthread_mutex_t) * (numb_of_philos + 1));
    if (!program->forks)
    {
        free (program->philos);
        return 1;
    }
    init1_helper(program, numb_of_philos);
    i = 0;
    while (i < numb_of_philos)
    {
        init2(&program->philos[i], i, program, numbers);
        i++;
    }
    return 0;
}


void    init2(t_philo *philo, int id, t_program *program, int *numbers)
{
    philo->id = id + 1;
    philo->eating = 0;
    philo->meals_eaten = 0;
    philo->last_meal = getcurrenttime();
    philo->start_time = philo->last_meal;
    philo->num_of_philos = numbers[0];
    philo->time_to_die = numbers[1];
    philo->time_to_eat = numbers[2];
    philo->time_to_sleep = numbers[3];
    if (numbers[4] != '\0')
        philo->num_times_to_eat = numbers[4];
    else
        philo->num_times_to_eat = -1;
    philo->dead = &program->dead_flag;
    philo->dead_lock = &program->dead_lock;
    philo->write_lock = &program->write_lock;
    philo->meal_lock = &program->meal_lock;
    philo->r_fork = &program->forks[id];
    philo->l_fork = &program->forks[(id + 1) % philo->num_of_philos];
}

int     create_threads(t_program *program,int num_of_philos)
{
    int i;

    i = 0;
    while (i < num_of_philos)
    {
        if (pthread_create(&program->philos[i].thread, NULL, routine, &program->philos[i]) != 0)
            return (printf ("Error creating a thread\n") ,1);
        i++;
    }
    if (pthread_create(&program->monitor_thread, NULL, monitor_routine, program) != 0)
        return (printf("Error creating monitor thread\n") ,1);
    return 0;
}
