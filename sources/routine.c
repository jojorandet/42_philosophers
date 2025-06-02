/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/29 10:49:30 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	waiting_for_forks(t_philo_data *philo) //fix the lcoal copy vs pointer pb here yyou 
//are accessiing the local fork copy and not the pointer itsself
{
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	t_global_data	*global;

	global = philo->global;
	first_fork = global->array_of_fork_locks[philo->fork[0]];
	second_fork = global->array_of_fork_locks[philo->fork[1]];
	pthread_mutex_lock(&first_fork);
	if (!log_philo_status(philo, GOT_FIRST_FORK))
	{
		pthread_mutex_unlock(&first_fork);
		return (0);
	}
	pthread_mutex_lock(&second_fork);
	if (!log_philo_status(philo, GOT_SECOND_FORK))
	{
		pthread_mutex_unlock(&first_fork);
		pthread_mutex_unlock(&second_fork);
	}
	return (1);
}

int	eating(t_philo_data *philo)
{
	t_global_data *global;
	
	global = philo->global;
	if (!(waiting_for_forks(philo)))
		return ;
	if (!log_philo_status(philo, EATING))
	{
		pthread_mutex_unlock(&global->array_of_fork_locks[philo->fork[0]]);
		pthread_mutex_unlock(&global->array_of_fork_locks[philo->fork[1]]);
	}
	pthread_mutex_lock(&philo->global->eating_time_lock);
	philo->global->eaten_at = get_time_in_ms();
	pthread_mutex_unlock(&philo->global->eating_time_lock);
	
	
}

void	start_philo_life_cycle(t_philo_data *philo)
{
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	t_global_data	*global;




}
/**
 * @brief philos always start by thinking, the time they
 * are thinking is the time where they can grab the forks.
 * during that time, when they have both forks they can start
 * eating.
 * 
 */
void	lone_philo_routine(t_philo_data *philo)
{
	t_global_data	*global;

	global = philo->global;
	log_philo_status(philo, THINKING);
	pthread_mutex_lock(&global->array_of_fork_locks[philo->fork[0]]);
	log_philo_status(philo, GOT_FIRST_FORK);
	ft_usleep(global->params.time_to_die);
	log_philo_status(philo, DIED);
	pthread_mutex_unlock(&global->array_of_fork_locks[philo->fork[0]]);
	return ;
}

void	*routine(void	*data)
{
	t_philo_data	*philo;
	t_global_data	*global;

	global = philo->global;
	philo = (t_philo_data *)data;
	if (philo->global->params.nb_philos == 1)
	{
		lone_philo_routine(philo);
		return (NULL);
	}
	start_philo_life_cycle(philo);
	return (NULL);
}
