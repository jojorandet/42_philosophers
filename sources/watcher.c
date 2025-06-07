/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:36:29 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 17:53:04 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->is_full_lock)
}

bool	philo_is_full_or_dead(t_main *main, int nb_ph, int time_to_die)
{
	int	philo_index;
	
	while (philo_index < nb_ph)
	{

		philo_index++;
	}
}

void	*watcher_routine(void *data)
{
	t_main	*main;
	int		nbr_philos;
	int		time_to_die;
	
	main = (t_main *)data;
	while (main->sim_is_running)
	{
		if (philo_is_full_or_dead)
		{
			pthread_mutex_lock(&main->sim_running_lock);
			main->sim_is_running = false;
			pthread_mutex_unlock(&main->sim_running_lock);
		}
	}
}