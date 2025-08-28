/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:59:05 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/28 16:16:39 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    init1(t_program *program, int *numbers)
{
    int numb_of_philos;
    int i;
    
    numb_of_philos = numbers[0];
    program->philos = malloc(sizeof(t_philo)*(numb_of_philos + 1));
    if (!program->philos)
        return 1;
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    i = 0;
    while (i < numb_of_philos)
    {
        init2(&program->philos[i], i, program, numbers);
        i++;
    }
    // program->philos[i] = '\0';
    return 0;
}

void    init2(t_philo *philo, int id, t_program *program, int *numbers)
{
    philo->id = id;
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
    //wait something missing here r_fork...
}
int     create_threads(t_program *program,int num_of_philos)
{
    int i;

    i = 0;
    while (i < num_of_philos)
    {
        if (pthread_create(&program->philos[i].thread, NULL, routine, &program->philos) != 0)
        {
            printf ("Error creating a thread");
            return 1;
        }
        i++;
    }
    return 0;
}



