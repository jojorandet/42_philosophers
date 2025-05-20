/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 14:53:41 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************** INCLUDES ***********************************/

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# define MAX_PHILO 200
# define STR_PROGRAM_NAME "./philo"
# define STR_HELP "Input error: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep]"
# define STR_NOT_NUM " %s: Input must be of type int. Must be between 0 and \
INT_MAX"
# define STR_INT_TOO_BIG "%s: Input %s above int_max, please give valid input."
# define STR_TOO_MANY_THREADS "%s: Exceeded the maximum amount of philosophers \
for optimal performance, please give <number_of_philosophes> <= %s"
# define STR_NEGATIVE_INPUT "%s: Input %s is negative, philosophers can only be \
positive :-)"
# define MALLOC_ERROR "Error: could not malloc, not enough space available."

/******************************** STRUCTURES *******************************/

typedef struct s_global_data t_global_data;

typedef struct				s_philo_data
{
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_philos;
	int						nbr_meals_per_philo;
	size_t					id;
	pthread_t				thread;
	unsigned int			meals_eaten;
	unsigned int			fork[2];
}							t_philo_data;

typedef struct				s_global_data
{
	pthread_mutex_t			*fork_mutexes;
	pthread_mutex_t			write_lock;
	bool					philo_is_dead;
	t_philo_data			*philo;
}							t_global_data;


/******************************* FUNCTIONS *********************************/

int							main(int argc, char **argv);
int							msg(char *help_msg, char *detail, int exit_no);


int							is_valid_input(int argc, char **argv);
int							is_int_max(char *s);
int							ft_atoi(char *s);

t_global_data				*init_global_data(t_global_data *global);

t_philo_data				*init_thread_data(int argc, char **argv, int n_philos);

int							start_philo_routine(t_global_data *table);
int							finish_philo_routine(t_global_data *table);

int							ft_strlen(char *s);
int							ft_strcmp(char *s1, char *s2);
void						ft_putstr_fd(char *s, int fd);
time_t						get_current_time_in_miliseconds(void);


void						destroy_mutexes(t_global_data *table);
void						exit_philo(t_global_data *table);


#endif