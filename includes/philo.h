/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/07 19:09:47 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PHILO 200
#define STR_PROGRAM_NAME "./philo"
#define STR_HELP "Input error: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"
#define STR_NOT_NUM " %s: Input must be of type int. Must be between 0 and \
INT_MAX"
#define STR_INT_TOO_BIG "%s: Input %s above int_max, please give valid input."
#define STR_TOO_MANY_THREADS "%s: Exceeded the maximum amount of philosophers \
for optimal performance, please give <number_of_philosophes> <= %s"
#define STR_NEGATIVE_INPUT "%s: Input %s is negative, philosophers can only be \
positive :-)"


int		main(int argc, char **argv);
int		is_valid_input(int argc, char **argv);
int 	msg(char *help_msg, char *detail, int exit_no);
//usleep uses unsigned int uscs, and then usleep(usecs)
//allowed printf


typedef struct	s_philo
{
	struct timeval	proc_start_t;
}				t_philo;



#endif