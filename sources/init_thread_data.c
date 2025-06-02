/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 20:27:46 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param fork[0] is the first fork the philosopher takes
 * grabs
 * @param fork[1] is the second fork the phoilosopher takes
 * Philosophers are always grabing the lowest indice fork
 * and then when it gets to the last philsoopher, we use
 * the modulo loop condition so that the order in which
 * it grabs the fork is reversed :)
 * it breaks the loop of waiting and avoids deadlock.
 */
void	assign_forks(t_philo_data *philosopher, int n_philos)
{
	int	first_fork;
	int	second_fork;
	int	left_fork;
	int	right_fork;

	left_fork = (philosopher->id + 1) % n_philos;
	right_fork = philosopher->id;
	if (left_fork < right_fork)
	{
		first_fork = left_fork;
		second_fork = right_fork;
	}
	else
	{
		first_fork = right_fork;
		second_fork = left_fork;
	}
	philosopher->fork[0] = first_fork;
	philosopher->fork[1] = second_fork;
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
		free_all_resources(global);
		return (NULL);
	}
	philo_i = 0;
	while (philo_i < global->params.nb_philos)
	{
		philos[philo_i].id = philo_i;
		philos[philo_i].meals_eaten = 0;
		philos[philo_i].last_meal = global->start_time;
		philos[philo_i].global = global;
		assign_forks(&philos[philo_i], global->params.nb_philos);
		philo_i++;
	}
	return (philos);
}
