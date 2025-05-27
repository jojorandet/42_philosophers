/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/27 10:53:42 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
 */
t_philo_data	*init_thread_data(t_global_data *global)
{
	t_philo_data		*philos;
	int					philo_i;


	printf("%d\n", global->params.nb_philos);
	philos = malloc(sizeof(t_philo_data) * global->params.nb_philos);
	if (!philos)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		exit_philo(global);
		return (false);
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
