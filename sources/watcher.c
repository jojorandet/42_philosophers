/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/04 18:16:24 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_is_done(t_philo *philo)
{
	bool	is_done;
	
	pthread_mutex_lock(&philo->is_done_lock);
	is_done = philo->is_done;
	pthread_mutex_unlock(&philo->is_done_lock);
	return (is_done);
}

long long	get_time_left(t_philo *philo, long long time_to_die)
{
	long long	current_time;
	long long	time_since_meal;

	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->last_meal_lock);
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (time_to_die - time_since_meal);
}

bool	philos_are_alive(t_main *main, int nbr_ph)
{
	int				i;
	t_philo			*philo;
	long long		time_left;
	long long		min_time_left;
	int				n_full_philos;

	philo = main->philo;
	time_left = 0;
	n_full_philos = 0;
	i = 0;
	min_time_left =	__LONG_LONG_MAX__;
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
				pthread_mutex_lock(&main->sim_end_lock);
				main->sim_has_ended = true;
				pthread_mutex_unlock(&main->sim_end_lock);
				return (false);
			}
			if (time_left < min_time_left)
				min_time_left = time_left;
		}
		i++;
	}
	if (n_full_philos == main->params.nb_philos)
	{
		printf("ENTERED THE CONDITION WHERE EQUAL\n");
		pthread_mutex_lock(&main->sim_end_lock);
		main->sim_has_ended = true;
		pthread_mutex_unlock(&main->sim_end_lock);
		return (false);
	}
	ft_usleep(50);
	return (true);
}

void	*watch_rounds(void *data)
{
	t_main			*main;
	int				nbr_philos;

	main = (t_main *)data;
	nbr_philos = main->params.nb_philos;
	while (main->sim_has_ended != true)
	{
		if (!philos_are_alive(main, nbr_philos))
			break ;
	}
	return (NULL);
}
