/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 17:26:51 by jrandet          ###   ########.fr       */
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

t_philo_data	*init_thread_data(t_global_data *global, t_param *params)
{
	t_philo_data		*philos;
	int					argc_index;
	int					philo_i;

	philos = malloc(sizeof(t_philo_data) * params->number_of_philos);
	if (!philos)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		return (false);
	}
	philo_i = 0;
	while (philo_i < params->number_of_philos)
	{
		philos[philo_i].param = *params;
		philos[philo_i].id = philo_i;
		philos[philo_i].meals_eaten = 0;
		philos[philo_i].write_lock = &global->write_lock;
		assign_forks(&philos[philo_i], params->number_of_philos);
		philo_i++;
	}
	return (philos);
}
