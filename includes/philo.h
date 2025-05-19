/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/19 18:40:38 by jrandet          ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct	s_philo
{
	pthread_t			thread;
	size_t				id;
	unsigned int		fork[2];
	unsigned int		has_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}				t_philo;

typedef struct	s_table
{
	int					number_of_philos;
	int					nbr_of_times_philo_must_eat;
	t_philo				*philo;
	pthread_mutex_t		*fork_mutexes;
}				t_table;


/******************************* FUNCTIONS *********************************/

int					main(int argc, char **argv);
int					msg(char *help_msg, char *detail, int exit_no);


int					is_valid_input(int argc, char **argv);
int					is_int_max(char *s);
int					ft_atoi(char *s);

t_table				*init_philo(int argc, char **argv, t_table *table);
int					start_philo_routine(t_table *table);
int					finish_philo_routine(t_table *table);

int					ft_strlen(char *s);
int					ft_strcmp(char *s1, char *s2);
time_t				get_time_in_miliseconds(void);


void				destroy_mutexes(t_table *table);
void				exit_philo(t_table *table);


#endif