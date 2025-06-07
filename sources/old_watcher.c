/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_watcher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 17:48:07 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool philo_is_done(t_philo *philo)
{
	bool philo_is_full;

	pthread_mutex_lock(&philo->is_full_lock);
	philo_is_full = philo->philo_is_full;
	pthread_mutex_unlock(&philo->is_full_lock);
	return (philo_is_full);
}

long long get_time_left(t_philo *philo, long long time_to_die)
{
	long long current_time;
	long long result;

	result = 0;
	pthread_mutex_lock(&philo->last_meal_lock);
	current_time = get_time_in_ms();
	result = philo->last_meal + time_to_die - current_time;
	if (result < 0)
		printf("NRG RES: result:    %lld   last meal: %lld, time to die: %lld and current time %lld\n\n", result, philo->last_meal, time_to_die, current_time);
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (result);
}

bool philos_are_alive(t_main *main, int nbr_ph)
{
	int i;
	t_philo *philo;
	long long time_left;
	long long min_time_left;
	int n_full_philos;

	philo = main->philo;
	time_left = 0;
	n_full_philos = 0;
	i = 0;
	min_time_left = __LONG_LONG_MAX__;
	while (i < nbr_ph)
	{
		if (philo_is_done(&philo[i]))
		{
			n_full_philos++;
		}
		else
		{
			time_left = get_time_left(&philo[i], main->params.time_to_die);
			if (time_left <= 0)
			{
				log_philo_status(&philo[i], DIED);
				return (false);
			}
			if (time_left < min_time_left)
				min_time_left = time_left;
		}
		i++;
	}
	if (n_full_philos == main->params.nb_philos)
		return (false);
	ft_usleep(min_time_left - 2);
	return (true);
}

void *watch_rounds(void *data)
{
	t_main *main;
	int nbr_philos;

	main = (t_main *)data;
	nbr_philos = main->params.nb_philos;
	while (main->sim_is_running)
	{
		if (!philos_are_alive(main, nbr_philos))
		{
			pthread_mutex_lock(&main->sim_running_lock);
			main->sim_is_running = false;
			pthread_mutex_unlock(&main->sim_running_lock);
		}
	}
	return (NULL);
}
