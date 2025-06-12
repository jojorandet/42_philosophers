/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:36:29 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/12 13:42:34 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	update_min_time_left(
	t_philo *philo,
	long long current_time,
	long long *min_time_left)
{
	long long	time_left;
	long long	time_to_die;

	time_left = 0;
	time_to_die = philo->main->params.time_to_die;
	pthread_mutex_lock(&philo->last_meal_lock);
	time_left = time_to_die - (current_time - philo->last_meal);
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (time_left < *min_time_left)
		*min_time_left = time_left;
}

static bool	philo_is_full(t_philo *philo)
{
	bool	is_full;

	pthread_mutex_lock(&philo->is_full_lock);
	is_full = philo->is_full;
	pthread_mutex_unlock(&philo->is_full_lock);
	return (is_full);
}

static bool	philo_is_full_or_dead(t_philo *philo, int nb_ph)
{
	int			number_of_full_philos;
	int			i;
	long long	min_time_left;
	long long	current_time;

	number_of_full_philos = 0;
	i = -1;
	min_time_left = __LONG_LONG_MAX__;
	current_time = get_time_in_ms();
	while (++i < nb_ph)
	{
		if (philo_is_full(&philo[i]))
			number_of_full_philos++;
		else
			update_min_time_left(&philo[i], current_time, &min_time_left);
		if (min_time_left < 0)
		{
			log_philo_status(philo, DIED);
			return (true);
		}
	}
	if (number_of_full_philos == philo->main->params.nb_philos)
		return (true);
	ft_sleep(min_time_left + 5);
	return (false);
}

/**
 * @param watcher thread is the thread which is in charge of monitoring 
 * the deaths and full philosopher and signaling that the simulation needs 
 * to stop.
 * @struct philo is a pointer in main, we will be working with the 
 * philo array 
 * @brief as long as the simulation is running (protected by lock because
 * it is set to true in the launch after each thread is created in the 
 * main thread). Else there would be a race condition.
 */
void	*watch_rounds(void *data)
{
	t_main	*main;
	t_philo	*philo;
	int		nbr_philos;

	main = (t_main *)data;
	philo = main->philo;
	nbr_philos = main->params.nb_philos;
	while (main->sim_is_running)
	{
		if (philo_is_full_or_dead(philo, nbr_philos))
		{
			pthread_mutex_lock(&main->sim_running_lock);
			main->sim_is_running = false;
			pthread_mutex_unlock(&main->sim_running_lock);
		}
	}
	return (NULL);
}
