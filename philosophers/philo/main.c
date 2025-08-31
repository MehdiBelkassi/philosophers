/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:28:10 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/30 16:45:09 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     parser(int argc, char **argv)
{
    int i;

    if (argc != 5 && argc != 6)
    {
        printf("false number of arguments\n");
        return 1;
    }
    i = 1;
    while(argv[i])
    {
        if (check_if_digit(argv[i]) == 1)
        {
            printf("only valid digits needed\n");  
            return 1;
        }
        if (two_in_one(argv[i]) == 1)
            return 1;
        i++;
    }
    return 0;
}

void    destroyer_and_joiner(t_program program)
{
    int i = 0;
    while (i < program.philos[0].num_of_philos)
    {
        pthread_join(program.philos[i].thread, NULL);
        i++;
    }
    pthread_join(program.monitor_thread, NULL);
    i = 0;
    while (i < program.philos[0].num_of_philos)
    {
        pthread_mutex_destroy(&program.forks[i]);
        i++;
    }
    pthread_mutex_destroy(&program.meal_lock);
    pthread_mutex_destroy(&program.dead_lock);
    pthread_mutex_destroy(&program.write_lock);
}

int main(int argc,char **argv)
{
    int *numbers;
    int i;
    t_program program;

    if (parser(argc, argv) == 1)
        return 1;
    numbers = malloc(sizeof(int) * (argc - 1 + 1));
    if (!numbers)
        return 1;
    i = 0;
    while (i < argc - 1)
    {
        numbers[i] = ft_atoi(argv[i + 1]);
        i++;
    }
    numbers[i] = '\0';
    if (check_arg(numbers, argc - 1 - 1) == 1 || init1(&program, numbers) == 1)
        return 1;
    if (create_threads(&program, numbers[0]) == 1)
        return 1;
    destroyer_and_joiner(program);
    free(numbers),free(program.philos);
    free(program.forks);
    return 0;
}
