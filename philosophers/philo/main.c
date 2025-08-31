/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:28:10 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/31 18:38:58 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
