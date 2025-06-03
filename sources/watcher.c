/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/03 16:04:33 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_time_until_death(t_philo_data *philo, long long time_to_die)
{
	long long current_time;
	long long time_since_meal;
	
	current_time = get_time_in_ms();
	pthread_mutex_lock(&philo->last_meal_lock);
	time_since_meal = current_time - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_lock);
	return (time_to_die - time_since_meal);
}

bool	philos_are_alive(t_main *main, int	nbr_ph)
{
	int				i;
	t_philo_data	*philo;
	long long		time_until_death;
	long long 		time_left;
	
	i = 0;
	philo = main->philo;
	time_left = main->params.time_to_die;
	time_until_death = 0;
	while (i < nbr_ph)
	{
		time_until_death = get_time_until_death(&philo[i], main->params.time_to_die);
		if (time_until_death <= 0)
		{
			log_philo_status(&philo[i], DIED);
			pthread_mutex_lock(&main->sim_end_lock);
			main->sim_has_ended = true;
			pthread_mutex_unlock(&main->sim_end_lock);
			return (false);
		}
		i++;
	}
	ft_usleep(time_left / 2);
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
		{
			pthread_mutex_lock(&main->sim_end_lock);
			main->sim_has_ended = true;
			pthread_mutex_unlock(&main->sim_end_lock);
			return (NULL);
		}
	}
	return (NULL);
}

//write thought process in pseudo code, you are capable enough to do this
//trust yurself
// two ways to know if the simulatipon has ended : in the output
//here i need to check 