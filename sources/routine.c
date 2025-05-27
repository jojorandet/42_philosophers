/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/27 14:42:38 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//sleeping routine is when a philo uses ft_usleep(time to sleeo)

//thinking time is when they are usign ft_usleep (time to sleep)

//just like when the philo is waiting to print, you need to get the action before that (timestamp)

// best to have uneven philosophers stard bythinknig , have a think routine function. 

//eat sleep routine
void	eat_sleep_routine(t_philo_data *philo)
{
	t_global_data *global;

	global = philo->global;
	pthread_mutex_lock(&global->fork_mutexes[philo->fork[0]]);
	log_philo_status(philo, GOT_FIRST_FORK);
	pthread_mutex_unlock(&global->fork_mutexes[philo->fork[0]]);
	// pthread_mutex_lock(&global->sim_end_lock);
	// global->sim_has_ended = true;
	// pthread_mutex_unlock(&global->sim_end_lock);
}
//as soon as a philo is dead, then the variable has to be written to 

void	*lone_philo_routine(t_philo_data *philo)
{
	t_global_data *global;

	global = philo->global;
	pthread_mutex_lock(&global->fork_mutexes[philo->fork[0]]);
	log_philo_status(philo, GOT_FIRST_FORK);
	ft_usleep(global->params.time_to_die);
	log_philo_status(philo, DIED);
	pthread_mutex_unlock(&global->fork_mutexes[philo->fork[0]]);
	return (NULL);
}

void	*routine(void	*data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)data;
	if (philo->global->params.nb_philos == 1)
		return (lone_philo_routine(philo));
	eat_sleep_routine(philo);
	return (NULL);
}
