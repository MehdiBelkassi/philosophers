/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:59:05 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/30 16:53:01 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *condition1(t_program *program, int i)
{
    pthread_mutex_unlock(&program->meal_lock);
    pthread_mutex_lock(&program->dead_lock);
    program->dead_flag = 1;
    pthread_mutex_unlock(&program->dead_lock);
    pthread_mutex_lock(&program->write_lock);
    printf("%zu %d died\n", getcurrenttime() - program->philos[i].start_time, program->philos[i].id);
    pthread_mutex_unlock(&program->write_lock);
    return (NULL);
}

void    *little_helper(t_program *program)
{
    pthread_mutex_lock(&program->dead_lock);
    program->dead_flag = 1;
    pthread_mutex_unlock(&program->dead_lock);
    return (NULL);
}

int	check_death(t_program *program, int i)
{
	pthread_mutex_lock(&program->meal_lock);
	if (getcurrenttime() - program->philos[i].last_meal >= program->philos[i].time_to_die)
		return (pthread_mutex_unlock(&program->meal_lock), 1);
	pthread_mutex_unlock(&program->meal_lock);
	return (0);
}

int	check_full(t_program *program, int i, int *all_full)
{
	if (program->philos[0].num_times_to_eat == -1)
		return (0);
	pthread_mutex_lock(&program->meal_lock);
	if (program->philos[i].meals_eaten < program->philos[0].num_times_to_eat)
		*all_full = 0;
	pthread_mutex_unlock(&program->meal_lock);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;
	int			i;
	int			all_full;

	program = (t_program *)arg;
	while (1)
	{
		all_full = 1;
		i = 0;
		while (i < program->philos[0].num_of_philos)
		{
			if (check_death(program, i))
				return (condition1(program, i));
			check_full(program, i, &all_full);
			i++;
		}
		if (all_full && program->philos[0].num_times_to_eat != -1)
			return (little_helper(program));
		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag == 1)
			return (pthread_mutex_unlock(&program->dead_lock), NULL);
		pthread_mutex_unlock(&program->dead_lock);
		usleep(100);
	}
	return (NULL);
}

