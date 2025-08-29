/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:59:05 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/29 16:33:37 by mbelkass         ###   ########.fr       */
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
    
    program->forks = malloc(sizeof(pthread_mutex_t) * (numb_of_philos + 1));
    if (!program->forks)
    {
        free (program->philos);
        return 1;
    }
    pthread_mutex_init(&program->meal_lock, NULL);
    pthread_mutex_init(&program->dead_lock, NULL);
    pthread_mutex_init(&program->write_lock, NULL);
    i = 0;
    while (i < numb_of_philos)
    {
        pthread_mutex_init(&program->forks[i], NULL);
        i++;
    }
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
    philo->l_fork = &program->forks[id];
    philo->r_fork = &program->forks[(id + 1) % philo->num_of_philos];
}

int     create_threads(t_program *program,int num_of_philos)
{
    int i;

    i = 0;
    while (i < num_of_philos)
    {
        if (pthread_create(&program->philos[i].thread, NULL, routine, &program->philos[i]) != 0)
        {

            printf ("Error creating a thread\n");
            return 1;
        }
        i++;
    }
    if (pthread_create(&program->monitor_thread, NULL, monitor_routine, program) != 0)
    {
        printf("Error creating monitor thread\n");
        return 1;
    }
    return 0;
}
void    *monitor_routine(void *arg)
{
    t_program *program = (t_program *)arg;
    int i;
    int all_full;

    while (1)
    {
        all_full = 1;
        i = 0;
        while (i < program->philos[0].num_of_philos)
        {
            pthread_mutex_lock(&program->meal_lock);
            if (getcurrenttime() - program->philos[i].last_meal >= program->philos[i].time_to_die)
            {
                pthread_mutex_unlock(&program->meal_lock);
                pthread_mutex_lock(&program->dead_lock);
                program->dead_flag = 1;
                pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_lock(&program->write_lock);
                printf("%zu %d died\n", getcurrenttime() - program->philos[i].start_time, program->philos[i].id);
                pthread_mutex_unlock(&program->write_lock);
                return (NULL); // Return to exit the thread
            }
            pthread_mutex_unlock(&program->meal_lock);

            if (program->philos[0].num_times_to_eat != -1)
            {
                pthread_mutex_lock(&program->meal_lock);
                if (program->philos[i].meals_eaten < program->philos[0].num_times_to_eat)
                {
                    all_full = 0;
                }
                pthread_mutex_unlock(&program->meal_lock);
            }
            i++;
        }

        if (all_full && program->philos[0].num_times_to_eat != -1)
        {
            pthread_mutex_lock(&program->dead_lock);
            program->dead_flag = 1;
            pthread_mutex_unlock(&program->dead_lock);
            return (NULL);
        }

        pthread_mutex_lock(&program->dead_lock);
        if (program->dead_flag == 1)
        {
            pthread_mutex_unlock(&program->dead_lock);
            return (NULL);
        }
        pthread_mutex_unlock(&program->dead_lock);

        usleep(100);
    }
    return (NULL);
}