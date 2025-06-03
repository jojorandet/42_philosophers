/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/03 15:29:38 by jrandet          ###   ########.fr       */
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
		return (0);
	}
	return (1);
}
/*
 * @param eating_at is the time at which the philo is eating. 
 * Important for the watcher who will use this data fir the time
 * checking throughout the simulation. This data is in milisec.
 * IMPORTANT: what data needs to be used here? 
 * time to eat, time to sleep.
 */
int	eating(t_philo_data *philo, pthread_mutex_t *ff, pthread_mutex_t *sf)
{
	if (!(wait_forks(philo, ff, sf)))
		return (0);
	if (!log_philo_status(philo, EATING))
	{
		pthread_mutex_unlock(ff);
		pthread_mutex_unlock(sf);
		return (0);
	}
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	ft_usleep(philo->main->params.time_to_eat);
	pthread_mutex_unlock(ff);
	pthread_mutex_unlock(sf);
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
	t_main			*main;

	main = philo->main;
	first_fork = &main->fork_array[philo->fork[0]];
	second_fork = &main->fork_array[philo->fork[1]];
	while (1)
	{
		if (!log_philo_status(philo, THINKING))
			return ;
		if (!eating(philo, first_fork, second_fork))
			return ;
		if (!log_philo_status(philo, SLEEPING))
			return ;
		ft_usleep(philo->main->params.time_to_sleep);
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
	t_main	*main;

	main = philo->main;
	log_philo_status(philo, THINKING);
	pthread_mutex_lock(&main->fork_array[philo->fork[0]]);
	log_philo_status(philo, GOT_FIRST_FORK);
	ft_usleep(main->params.time_to_die);
	log_philo_status(philo, DIED);
	pthread_mutex_unlock(&main->fork_array[philo->fork[0]]);
	return ;
}

void	*routine(void	*data)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)data;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = philo->main->start_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (philo->main->params.nb_philos == 1)
	{
		lone_philo_routine(philo);
		return (NULL);
	}
	start_philo_life_cycle(philo);
	return (NULL);
}
