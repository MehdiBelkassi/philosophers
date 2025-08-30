/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:28:10 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/29 16:25:33 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc,char **argv)
{
    
    int len;
    int *numbers;
    int i;
    t_program program;

    if (argc != 5 && argc != 6)
    {
        printf("false number of arguments\n");
        return 1;
    }
    len = argc - 1;
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
    numbers = malloc(sizeof(int) * (len + 1));
    if (!numbers)
        return 1;
    i = 0;
    while (i < argc - 1)
    {
        numbers[i] = ft_atoi(argv[i + 1]);
        i++;
    }
    numbers[i] = '\0';
    if (check_arguments(numbers, len - 1) == 1)
        return 1;
    //init 
    init1(&program, numbers);

    
    if (create_threads(&program, numbers[0]) == 1)
        return 1;
    i = 0;
    
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
    
    
    return 0;
}







// int main(int argc, char **argv)
// {
//     int len;
//     int *numbers;
//     int i;
//     t_program program;

//     if (argc != 5 && argc != 6)
//     {
//         printf("false number of arguments\n");
//         return 1;
//     }
//     len = argc - 1;
//     i = 1;
//     while(argv[i])
//     {
//         if (check_if_digit(argv[i]) == 1)
//         {
//             printf("only valid digits needed\n");
//             return 1;
//         }
//         if (two_in_one(argv[i]) == 1)
//             return 1;
//         i++;
//     }
//     numbers = malloc(sizeof(int) * (len + 1));
//     if (!numbers)
//         return 1;
//     i = 0;
//     while (i < argc - 1)
//     {
//         numbers[i] = ft_atoi(argv[i + 1]);
//         i++;
//     }
//     numbers[i] = '\0';
//     if (check_arguments(numbers, len) == 1)
//     {
//         free(numbers);
//         return 1;
//     }
//     if (init1(&program, numbers) == 1)
//     {
//         free(numbers);
//         return 1;
//     }
//     free(numbers);
//     if (create_threads(&program, program.philos[0].num_of_philos) == 1)
//     {
//         // Cleanup on thread creation failure
//         free(program.philos);
//         free(program.forks);
//         return 1;
//     }
    
//     // // Create the monitor thread
//     // if (pthread_create(&program.monitor_thread, NULL, monitor_routine, &program) != 0)
//     // {
//     //     // Cleanup on monitor creation failure
//     //     free(program.philos);
//     //     free(program.forks);
//     //     return 1;
//     // }

//     // Wait for all threads to finish their execution
//     i = 0;
//     while (i < program.philos[0].num_of_philos)
//     {
//         pthread_join(program.philos[i].thread, NULL);
//         i++;
//         //segv
//     }
//     pthread_join(program.monitor_thread, NULL);

//     // Cleanup: Destroy mutexes and free allocated memory
//     i = 0;
//     while (i < program.philos[0].num_of_philos)
//     {
//         pthread_mutex_destroy(&program.forks[i]);
//         i++;
//     }
//     pthread_mutex_destroy(&program.meal_lock);
//     pthread_mutex_destroy(&program.dead_lock);
//     pthread_mutex_destroy(&program.write_lock);
    
//     free(program.philos);
//     free(program.forks);

//     return 0;
// }