/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 23:09:02 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 23:48:53 by jrandet          ###   ########.fr       */
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



void	*watch_rounds(void *data)
{
	t_global_data	*global;
	int				nbr_philos;
	int				time_to_die;

	global = (t_global_data *)data;
	nbr_philos = global->params.nb_philos;
	time_to_die = global->params.time_to_die;
	
}