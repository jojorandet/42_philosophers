/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_stop_routine.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 13:54:24 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/19 17:05:34 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void	*data)
{
	t_philo		*philo;
	pthread_t	tid;

	tid = pthread_self();
	philo = (t_philo *)data;
	printf("for philo %ld thread[%ld] has been created.\n", philo->id, tid);
	//sleep
	//think
	//repeat
	return (NULL);
}

/*
*	pthread_create:
*	thread: a pointer to the pthread_t variable type that we need to send, the thread id
*	attr is NULL 
*	args is a pointer to pass to the routie function, if more than one we need to send a struct
*/
int	start_philo_routine(t_table *table)
{
	int			i;
	int			status;

	i = 0;
	status = 0;
	while (i < table->number_of_philos)
	{
		status = pthread_create(&table->philo[i].thread, NULL, philo_routine, &table->philo[i]);
		if (status != 0)
		{
			while (i--)
			{
				pthread_detach(table->philo[i].thread);
			}
			return (msg("Error: pthread_create failed.\n", \
				 NULL, EXIT_FAILURE), false); //scenariowhere it does not work 
		}
		i++;
	}
	return (true);
}

int	finish_philo_routine(t_table *table)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < table->number_of_philos)
	{
		status = pthread_join(table->philo[i].thread, NULL);
		if (status != 0)
		{
			return (msg("Error: pthread_join failed.\n", \
				 NULL, EXIT_FAILURE), false); //scenariowhere it does not work
		}
		i++;
	}
	destroy_mutexes(table);
	return (true);
}
