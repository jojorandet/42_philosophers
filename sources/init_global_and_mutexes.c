/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_and_mutexes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/28 13:01:45 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * initialised here :) There is an array of mutexes for the forks. 
*/
static pthread_mutex_t	*init_global_fork_mutex(t_global_data *global)
{
	pthread_mutex_t		*fork_mutexes;
	int					i;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * global->params.nb_philos);
	if (!fork_mutexes)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		exit_philo(global);
		return (NULL);
	}
	while (i < global->params.nb_philos)
	{
		pthread_mutex_init(&fork_mutexes[i], 0);
		i++;
	}
	return (fork_mutexes);
}

/**
 * @param fork_mutexes is an array of mutexes, or locks
 * When you have a section of code which is a critical section, it needs 
 * to be protected by locks in order to operate as desired. 
 * if no thread has the lock, then the thread accessing it first gets it.
 * The thread waiting for the lock will not be able to return until it has 
 * acquired the lock. Only the thread who has the lock can unlock the shared
 * variable
 * 
 * ALL locks must be initialised in order for them to have the correct
 * values to begin with and thus work when lock/unlocked are called.
 * When you are done, you need to detroy the mutexes. 
 * 
 */
static bool	initialise_global_mutexes(t_global_data *global)
{
	if (!(global->fork_mutexes = init_global_fork_mutex(global)))
		return (false);
	pthread_mutex_init(&global->write_lock, NULL);
	pthread_mutex_init(&global->sim_end_lock, NULL);
	return (true);
}

bool	init_global_struct(t_global_data *global, t_param *params)
{
	global->start_time = 0;
	global->time_stamp = 0;
	global->params = *params;
	global->philo_is_dead = false;
	global->sim_has_ended = false;
	return (initialise_global_mutexes(global));
}
