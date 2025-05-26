/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_stop_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:24 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 10:09:05 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo_routine(t_global_data *global)
{
	t_philo_data		*philo;
	int					i;
	
	philo = global->philo;
	i = 0;
	while (i < philo->param.nb_philos)
	{
		philo[i].start_time = get_time_usec();
		//   * philo->param.nb_philos * 2 * 10;
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

int	finish_philo_routine(t_global_data *global)
{
	t_philo_data		*philo;
	int					i;

	philo = global->philo;
	i = 0;
	while (i < philo->param.nb_philos)
	{
		if (pthread_join(global->philo[i].thread, NULL) != 0)
			return (msg("Error: pthread_join failed.\n", \
				NULL, EXIT_FAILURE), false);
		i++;
	}
	destroy_mutexes(global);
	return (true);
}
