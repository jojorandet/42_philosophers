/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/23 15:19:37 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_global_fork_mutex(t_philo_data *philo)
{
	pthread_mutex_t		*fork_mutexes;
	int					i;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * philo->param.nb_philos); //segfault here
	while (i < philo->param.nb_philos)
	{
		pthread_mutex_init(&fork_mutexes[i], 0);
		printf("the mutex is initialised for fork number %d\n", i);
		i++;
	}
	return (fork_mutexes);
}

void	initialise_global_mutexes(t_global_data *global)
{
	global->fork_mutexes = init_global_fork_mutex(global->philo);
	pthread_mutex_init(&global->write_lock, NULL);
}
