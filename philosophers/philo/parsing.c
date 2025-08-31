/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:56:15 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/30 16:44:33 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int     check_if_digit(char *str)
{
    int i;
    
    if (!str)
        return 0;
    i = 0;

    while (str[i])
    {
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break;
        if (str[i] < '0' || str[i] > '9')
            return 1;
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\0')
            break;
        
        i++;
    }
    return 0;
}

int     check_arg(int *str, int len)
{
    int flag;

    flag = 1;
    
    if (str[0] > 200)
    {
        printf("the philosophes are more than 200\n");
        return 1;
    }
    while (len != -1)                                                                                                          
    {
        if (str[len] == 0 && !flag)
            return 1;
        if (str[len] < 0)
            return 1;
        flag = 0;
        len--;
    }
    return 0;
}

int     two_in_one(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        while (str[i] && str[i] == ' ')
            i++;
        while(str[i] >= '0' && str[i] <= '9')
            i++;
        while (str[i] && str[i] == ' ')
            i++;
        if (str[i] == '\0')
            return 0;
        else
            return 1;
    }
    return 0;
}
