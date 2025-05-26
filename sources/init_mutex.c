/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 11:54:18 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_global_fork_mutex(t_global_data *global)
{
	pthread_mutex_t		*fork_mutexes;
	int					i;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * global->params.nb_philos);
	while (i < global->params.nb_philos)
	{
		pthread_mutex_init(&fork_mutexes[i], 0);
		i++;
	}
	return (fork_mutexes);
}

void	initialise_global_mutexes(t_global_data *global)
{
	global->fork_mutexes = init_global_fork_mutex(global);
	pthread_mutex_init(&global->write_lock, NULL);
}

void	init_global_struct(t_global_data *global, t_param *params)
{
	global->start_time = 0;
	global->params = *params;
	global->philo_is_dead = false;
	initialise_global_mutexes(global);
}
