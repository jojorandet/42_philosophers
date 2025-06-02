/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 13:07:55 by jrandet          ###   ########.fr       */
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


void	*watch_rounds(void *data)
{
	t_global_data	*global;
	int				nbr_philos;
	int				time_to_die;

	global = (t_global_data *)data;
	nbr_philos = global->params.nb_philos;
	time_to_die = global->params.time_to_die;
	printf("nb ohilos: %d, time_to_die: %d\n", nbr_philos, time_to_die);
	start_watch_routine(nbr_philos, time_to_die);

	return (NULL);
}
