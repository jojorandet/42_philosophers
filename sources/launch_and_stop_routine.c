/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_stop_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:24 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 14:45:10 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void	*data)
{
	t_philo_data		*philo;
	pthread_t				tid;

	tid = pthread_self();
	philo = (t_philo_data *)data;
	printf("for philo %ld thread[%ld] has been created.\n", philo->id, tid);
	return (NULL);
}

int	finish_philo_routine(t_global_data *global)
{
	t_philo_data	*philo;
	int					i;
	int					status;

	philo = global->philo;
	i = 0;
	status = 0;
	while (i < philo->number_of_philos)
	{
		status = pthread_join(global->philo[i].thread, NULL);
		if (status != 0)
		{
			return (msg("Error: pthread_join failed.\n", \
				NULL, EXIT_FAILURE), false);
		}
		i++;
	}
	destroy_mutexes(global);
	return (true);
}

int	start_philo_routine(t_global_data *global)
{
	t_philo_data	*philo;
	int					i;
	int					status;

	philo = global->philo;
	i = 0;
	status = 0;
	while (i < philo->number_of_philos)
	{
		status = pthread_create(&philo[i].thread, NULL, philo_routine, \
			&global->philo[i]);
		if (status != 0)
		{
			while (i--)
			{
				pthread_detach(philo[i].thread);
			}
			return (msg("Error: pthread_create failed.\n", \
				NULL, EXIT_FAILURE), false);
		}
		printf("Pthread create number %d\n", i);
		i++;
	}
	return (true);
}
