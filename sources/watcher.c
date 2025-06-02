/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 16:53:57 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * time calculation function to find out the time
 */
// last meal + time to die
// if the curent time is bigger than this, then the philo had died
//log output to DIED and send the signal to stop the simulation

//the result of the above function can be 
// if the above result is less thsan 0, meaning the current time is bigeer than the last meal + time to die, 
// then die
//if not, then not sure yet calculate tomorrow
// but in the case where the philo does not die, then we need to check again


//try and gigure this time thing out :)

bool	philos_are_alive(t_global_data *global, int	nbr_ph)
{
	int i;
	long long		time_since_last_meal;
	long long		current_time;
	t_philo_data	*philo;

	i = 0;
	philo = global->philo;
	current_time = get_time_in_ms();
	while (i < nbr_ph)
	{
		time_since_last_meal = current_time - philo[i].last_meal;
		//printf("time since last meal: %lld and last meal: %lld\n", time_since_last_meal, philo[i].last_meal);
		if (time_since_last_meal >= global->params.time_to_die)
		{
			log_philo_status(&philo[i], DIED);
			pthread_mutex_lock(&global->sim_end_lock);
			global->sim_has_ended = true;
			pthread_mutex_unlock(&global->sim_end_lock);
			return (false);
		}
		i++;
	}
	return (true);
}


void	*watch_rounds(void *data)
{
	t_global_data	*global;
	int				nbr_philos;

	global = (t_global_data *)data;
	nbr_philos = global->params.nb_philos;
	while (global->sim_has_ended != true)
	{
		if (!philos_are_alive(global, nbr_philos))
		{
			global->sim_has_ended = true;
			return (NULL);
		}
	}
	return (NULL);
}

//write thought process in pseudo code, you are capable enough to do this
//trust yurself
// two ways to know if the simulatipon has ended : in the output
//here i need to check 