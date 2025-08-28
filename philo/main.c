/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:28:10 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/27 15:51:48 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc,char **argv)
{
    
    int len;
    int *numbers;
    int i;
    t_program program;
    // t_philo philo;

    
    if (argc != 5 && argc != 6)   // should have 5 numbers or 4
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
    
    return 0;
}
