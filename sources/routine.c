/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/23 15:57:45 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"




void	*routine(void	*data)
{
	t_philo_data			*philo;
	pthread_t				tid;

	tid = pthread_self();
	philo = (t_philo_data *)data;
	// if (philo->param.nb_philos == 1)
	// 	lone_philo_routine(philo);
	printf("philo %ld (thread %ld) is created and will begin the routine at %ld ms\n", philo->id, tid, philo->start_time);
	return (NULL);
}