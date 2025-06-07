/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:29:43 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 15:41:46 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void wait_for_start(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->main->sim_running_lock);
		if (philo->main->sim_is_running == true)
		{
			pthread_mutex_unlock(&philo->main->sim_running_lock);
			break;
		}
		pthread_mutex_unlock(&philo->main->sim_running_lock);
		usleep(100);
	}
}
/*
 * @param eating_at is the time at which the philo is eating.
 * Important for the watcher who will use this data fir the time
 * checking throughout the simulation. This data is in milisec.
 * IMPORTANT: what data needs to be used here?
 * time to eat, time to sleep.
 */
int eating(t_philo *philo)
{
	pthread_mutex_t *first_fork;
	pthread_mutex_t *second_fork;

	if (!(wait_forks(philo, &first_fork, &second_fork)))
		return (0);
	if (!log_philo_status(philo, EATING))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->last_meal_lock);
	ft_usleep(philo->main->params.time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	return (1);
}

/**
 * two ways for simulation to end:
 * 1. Philosopher starves and dies
 * 2. Philsophers have all eaten enough times, stop
 * so during the loop, need to check both of these conditions.
 */
void start_philo_life_cycle(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->main->sim_running_lock);
		if (philo->main->sim_is_running == false)
		{
			pthread_mutex_unlock(&philo->main->sim_running_lock);
			return;
		}
		pthread_mutex_unlock(&philo->main->sim_running_lock);
		if (!log_philo_status(philo, THINKING))
			return;
		if (!eating(philo))
			return;
		pthread_mutex_lock(&philo->last_meal_lock);
		if (philo->meals_eaten == philo->main->params.nbr_meals_per_philo)
		{
			pthread_mutex_unlock(&philo->last_meal_lock);
			pthread_mutex_lock(&philo->is_done_lock);
			philo->is_done = true;
			pthread_mutex_unlock(&philo->is_done_lock);
			return;
		}
		pthread_mutex_unlock(&philo->last_meal_lock);
		if (!log_philo_status(philo, SLEEPING))
			return;
		ft_usleep(philo->main->params.time_to_sleep);
	}
}

/**
 * Lone philo routine is to ensure that the case of the
 * one philo is treated.
 * Grabs one fork. waits, dies.  In this case, I chose
 * to have the philo pick the fork on his left defacto,
 * so that the lone philo routine does not depend on the
 * fork assignment.
 */
void lone_philo_routine(t_philo *philo)
{
	t_main *main;

	main = philo->main;
	log_philo_status(philo, THINKING);
	pthread_mutex_lock(philo->left_fork);
	log_philo_status(philo, GOT_FIRST_FORK);
	ft_usleep(main->params.time_to_die);
	log_philo_status(philo, DIED);
	pthread_mutex_unlock(philo->left_fork);
	return;
}

void *routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = philo->main->start_time;
	pthread_mutex_unlock(&philo->last_meal_lock);
	wait_for_start(philo);
	if (philo->main->params.nb_philos == 1)
	{
		lone_philo_routine(philo);
		return (NULL);
	}
	start_philo_life_cycle(philo);
	return (NULL);
}
