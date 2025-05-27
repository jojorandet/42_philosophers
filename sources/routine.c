/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/27 10:46:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//sleeping routine is when a philo uses ft_usleep(time to sleeo)

//thinking time is when they are usign ft_usleep (time to sleep)

//just like when the philo is waiting to print, you need to get the action before that (timestamp)

// best to have uneven philosophers stard bythinknig , have a think routine function. 

//eat sleep routine



void	lone_philo_routine(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->global->fork_mutexes[philo->fork[0]]);
	log_philo_status(philo->global, GOT_FIRST_FORK);
	ft_usleep(philo->global->params.time_to_die);
	log_philo_status(philo->global, DIED);
	pthread_mutex_unlock(&philo->global->fork_mutexes[philo->fork[0]]);
}

void	*routine(void	*data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)data;
	if (philo->global->params.nb_philos == 1)
		lone_philo_routine(philo);
	return (NULL);
}
