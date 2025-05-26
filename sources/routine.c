/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 19:43:02 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
	t_philo_data			*philo;

	philo = (t_philo_data *)data;
	if (philo->global->params.nb_philos == 1)
		lone_philo_routine(philo);

	return (NULL);
}
