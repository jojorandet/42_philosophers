/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main_and_mutexes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/04 15:42:00 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * initialised here :) There is an array of mutexes for the forks.
 */
static pthread_mutex_t *init_main_fork_mutex(t_main *main)
{
	pthread_mutex_t *fork_array;
	int i;

	i = 0;
	fork_array = malloc(sizeof(pthread_mutex_t) * main->params.nb_philos);
	if (!fork_array)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		free_all_resources(main);
		return (NULL);
	}
	while (i < main->params.nb_philos)
	{
		pthread_mutex_init(&fork_array[i], 0);
		i++;
	}
	return (fork_array);
}

/**
 * @param fork_array is an array of mutexes, or locks
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
static bool initialise_main_mutexes(t_main *main)
{
	main->fork_array = init_main_fork_mutex(main);
	if (!(main->fork_array))
		return (false);
	pthread_mutex_init(&main->write_lock, NULL);
	pthread_mutex_init(&main->sim_running_lock, NULL);
	return (true);
}

bool init_main_struct(t_main *main, t_param *params)
{
	main->params = *params;
	main->sim_is_running = false;
	return (initialise_main_mutexes(main));
}
