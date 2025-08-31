/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbelkass <mbelkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 22:38:03 by mbelkass          #+#    #+#             */
/*   Updated: 2025/08/31 18:37:57 by mbelkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
typedef struct s_program t_program;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t *forks;
	pthread_t       monitor_thread;
	t_philo			*philos;
}					t_program;

int	    ft_atoi(const char *str);
int     ft_strlen(int *str);
int     check_if_digit(char *str);
int     check_arg(int *str, int len);
int     two_in_one(char *str);
size_t  getcurrenttime(void);
int    	init1(t_program *program, int *numbers);
void    init2(t_philo *philo, int id, t_program *program, int *numbers);
int     create_threads(t_program *program,int num_of_philos);
int    ft_usleep(size_t time);
void    think(t_philo *philo);
void    ft_sleep(t_philo *philo);
void    *routine(void *arg);
void 	*monitor(void *arg);
void    eat(t_philo *philo);
void    *monitor_routine(void *arg);
void    print_status(t_philo *philo, const char *status);
