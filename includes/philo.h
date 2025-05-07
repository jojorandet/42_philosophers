/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/07 18:27:42 by jrandet          ###   ########.fr       */
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


#define STR_HELP "Input error: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep>"
#define STR_NOT_NUM " %s: Input must be of type int. Must be between 0 and \
INT_MAX"


int		main(int argc, char **argv);
int		is_valid_input(int argc, char **argv);
int		msg(char *help_msg, int exit_no);
//usleep uses unsigned int uscs, and then usleep(usecs)
//allowed printf


typedef struct	s_philo
{
	struct timeval	proc_start_t;
}				t_philo;



#endif