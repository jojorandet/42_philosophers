/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/27 12:31:47 by jrandet          ###   ########.fr       */
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
//above the time left, in whhich case 

//two things he needs to check: has the philo eaten at least x meals?

// has the philo died?

void	*watch_rounds(void *data)
{
	t_global_data	*global;
	int				nbr_philos;
	int				time_to_die;

	global = (t_global_data *)data;
	printf("%d\n", global->params.nb_philos);
	nbr_philos = global->params.nb_philos;
	time_to_die = global->params.time_to_die;
	printf("the watcher is created, nb_philos: %d and time_to_die: %d\n", nbr_philos, time_to_die);
	(void)time_to_die;
	(void)nbr_philos;
	return (NULL);
}
