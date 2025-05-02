/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/01 18:40:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int	main(int argc, char **argv);
//usleep uses unsigned int uscs, and then usleep(usecs)
//allowed printf


typedef struct	s_philo
{
	struct timeval	process_start_time;
}				t_philo;



#endif