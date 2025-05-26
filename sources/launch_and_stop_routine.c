/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_stop_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:24 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 12:50:57 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * in pthread create, i send thei individual philo routine 
 * @param start time is a global data because its shared among all threads 
 */
int	start_philo_routine(t_global_data *global)
{
	t_philo_data		*philo;
	int					i;
	
	philo = global->philo;
	i = 0;
	while (i < global->params.nb_philos)
	{
		global->start_time = get_time_usec();
		if (pthread_create(&philo[i].thread, NULL, log_philo_status , &philo[i]) != 0)
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
	destroy_mutexes(global);
	
	return (true);
}
