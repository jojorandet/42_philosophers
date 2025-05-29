/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_and_mutexes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/29 10:27:46 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * initialised here :) There is an array of mutexes for the forks. 
*/
static pthread_mutex_t	*init_global_fork_mutex(t_global_data *global)
{
	pthread_mutex_t		*array_of_fork_locks;
	int					i;

	i = 0;
	array_of_fork_locks = malloc(sizeof(pthread_mutex_t) * global->params.nb_philos);
	if (!array_of_fork_locks)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		exit_philo(global);
		return (NULL);
	}
	while (i < global->params.nb_philos)
	{
		pthread_mutex_init(&array_of_fork_locks[i], 0);
		i++;
	}
	return (array_of_fork_locks);
}

/**
 * @param array_of_fork_locks is an array of mutexes, or locks
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
	if (!(global->array_of_fork_locks = init_global_fork_mutex(global)))
		return (false);
	pthread_mutex_init(&global->write_lock, NULL);
	pthread_mutex_init(&global->sim_end_lock, NULL);
	pthread_mutex_init(&global->eating_time_lock, NULL);
	return (true);
}

bool	init_global_struct(t_global_data *global, t_param *params)
{
	global->start_time = 0;
	global->eaten_at = 0;
	global->params = *params;
	global->sim_has_ended = false;
	return (initialise_global_mutexes(global));
}
