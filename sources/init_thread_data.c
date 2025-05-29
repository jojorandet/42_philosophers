/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/29 11:05:41 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param fork[0] is the first fork the philosopher takes
 * grabs
 * @param fork[1] is the second fork the phoilosopher takes
 * Philosophers start at 0. 
 * Even philosophers grab their fork on the right first at the begining 
 * of the simulation. Even = right handed.
 * Odd philosophers grab their fork on the left first at the begining.
 * Odd = left handed.
 * 
 * This is done to avoid the scenario of philos eternally waiting on a
 * fork, which another philo is waiting for etc. DEADLOCK.
 */
void	assign_forks(t_philo_data *philosopher, int n_philos)
{
	if (philosopher->id % 2 == 0)
	{
		philosopher->fork[0] = (philosopher->id + 1) % n_philos;
		philosopher->fork[1] = philosopher->id;
	}
	else
	{
		philosopher->fork[0] = philosopher->id;
		philosopher->fork[1] = (philosopher->id + 1) % n_philos;
	}
}

/**
 * Table of threads, useful for the monitor to traverse and see which
 * philo needs to be taken care of.
 * 
 * @return is the pointer to the array of philo structures.
 */
t_philo_data	*init_thread_data(t_global_data *global)
{
	t_philo_data		*philos;
	int					philo_i;

	philos = malloc(sizeof(t_philo_data) * global->params.nb_philos);
	if (!philos)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		exit_philo(global);
		return (NULL);
	}
	philo_i = 0;
	while (philo_i < global->params.nb_philos)
	{
		philos[philo_i].id = philo_i;
		philos[philo_i].meals_eaten = 0;
		philos[philo_i].global = global;
		assign_forks(&philos[philo_i], global->params.nb_philos);
		philo_i++;
	}
	return (philos);
}
