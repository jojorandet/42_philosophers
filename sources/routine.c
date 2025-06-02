/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 16:21:28 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * when the philo is waiting to eat, he is thinking.
 * 
 */
int	wait_forks(t_philo_data *philo, pthread_mutex_t *ff, pthread_mutex_t *sf)
{
	pthread_mutex_lock(ff);
	if (!log_philo_status(philo, GOT_FIRST_FORK))
	{
		pthread_mutex_unlock(ff);
		return (0);
	}
	pthread_mutex_lock(sf);
	if (!log_philo_status(philo, GOT_SECOND_FORK))
	{
		pthread_mutex_unlock(ff);
		pthread_mutex_unlock(sf);
	}
	return (1);
}
/**
 * @param eating_at is the time at which the philo is eating. 
 * Important for the watcher who will use this data fir the time
 * checking throughout the simulation. This data is in milisec.
 * IMPORTANT: what data needs to be used here? 
 * time to eat, time to sleep.
 */
int	eating(t_philo_data *philo, pthread_mutex_t *ff, pthread_mutex_t *sf)
{
	if (!(wait_forks(philo, ff, sf))) //if he has the fork, this will be 1
		return (0);
	if (!log_philo_status(philo, EATING))
	{
		pthread_mutex_unlock(ff);
		pthread_mutex_unlock(sf);
		return (0);
	}
	philo->last_meal = get_time_in_ms();
	ft_usleep(philo->global->params.time_to_eat);
	return (1);
}
/**
 * two ways for simulation to end:
 * 1. Philosopher starves and dies
 * 2. Philsophers have all eaten enough times, stop
 * so during the loop, need to check both of these conditions.
 */
void	start_philo_life_cycle(t_philo_data *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_global_data	*global;

	global = philo->global;
	first_fork = &global->fork_array[philo->fork[0]];
	second_fork = &global->fork_array[philo->fork[1]];
	while (1)
	{
		if (!log_philo_status(philo, THINKING))
			return ;
		if (!eating(philo, first_fork, second_fork))
			return ;
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		if (!log_philo_status(philo, SLEEPING))
			return ;
		ft_usleep(philo->global->params.time_to_sleep);
	//if the sim has stopped, which is when a philo dies, it will return
	//if the philo have eaten, then you can also stop the simulation
	}
}
/**
 * @brief philos always start by thinking, the time they
 * are thinking is the time where they can grab the forks.
 * during that time, when they have both forks they can start
 * eating.
 * Lone philo routine is to ensure that the case of the
 * one philo is treated.
 * Grabs one fork. waits, dies.
 */
void	lone_philo_routine(t_philo_data *philo)
{
	t_global_data	*global;

	global = philo->global;
	log_philo_status(philo, THINKING);
	pthread_mutex_lock(&global->fork_array[philo->fork[0]]);
	log_philo_status(philo, GOT_FIRST_FORK);
	ft_usleep(global->params.time_to_die);
	log_philo_status(philo, DIED);
	pthread_mutex_unlock(&global->fork_array[philo->fork[0]]);
	return ;
}

void	*routine(void	*data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)data;
	philo->last_meal = philo->global->start_time;
	if (philo->global->params.nb_philos == 1)
	{
		lone_philo_routine(philo);
		return (NULL);
	}
	start_philo_life_cycle(philo);
	return (NULL);
}
