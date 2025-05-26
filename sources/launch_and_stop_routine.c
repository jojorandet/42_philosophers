/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_stop_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:24 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 19:44:48 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @function the pthread create function takes four arguments
 * @param thread is a pointer to a struct of type pthread_t
 * This structure is used to interact with the thread, so we need to pass it 
 * to pthread create to start interacting with it.
 * @param attr use the pthread_attr_init() if you want to be specific about
 * stack size, but in most cases NULL is sufficient. 
 * @param start_routine is the fucntion the thread should start running in, 
 * we send a function pointer. havoing a void pointer allows us to pass any 
 * pointer 
 * @param arg os the argument passed to the start routine.
 * in pthread create, i send thei individual philo routine 
 * @param start_time is a global data because its shared among all threads 
 * and they a;; start at the same time
 * the loop for the creation of threads takes no tie at all 
 */
int	start_philo_routine(t_global_data *global)
{
	t_philo_data		*philo;
	int					i;
	
	philo = global->philo;
	i = 0;
	while (i < global->params.nb_philos)
	{
		global->start_time = get_time_in_ms();
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			while (i--)
				pthread_detach(philo[i].thread);
			return (msg("Error: pthread_create failed.\n", \
				NULL, EXIT_FAILURE), false);
		}
		i++;
	}
	return (true);
}

/**
 * when you want to wait for threads to complete, you use pthread_join. 
 */
int	finish_philo_routine(t_global_data *global)
{
	int					i;

	i = 0;
	while (i < global->params.nb_philos)
	{
		if (pthread_join(global->philo[i].thread, NULL) != 0)
			return (msg("Error: pthread_join failed.\n", \
				NULL, EXIT_FAILURE), false);
		i++;
	}
	exit_philo(global);
	return (true);
}
