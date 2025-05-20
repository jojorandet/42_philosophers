/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 14:57:23 by jrandet          ###   ########.fr       */
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
	printf("philo[%ld] first takes fork %d and then fork %d\n", philosopher->id, philosopher->fork[0], philosopher->fork[1]);
}

t_philo_data	*init_thread_data(int argc, char **av, int n_philos)
{
	t_philo_data		*philo;
	int					argc_index;
	int					philo_i;

	philo = malloc(sizeof(t_philo_data) * n_philos);
	if (!philo)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		return (false);
	}
	philo_i = 0;
	while (philo_i < n_philos)
	{
		argc_index = 2;
		philo[philo_i].number_of_philos = n_philos;
		philo[philo_i].time_to_die = ft_atoi(av[argc_index++]);
		philo[philo_i].time_to_eat = ft_atoi(av[argc_index++]);
		philo[philo_i].time_to_sleep = ft_atoi(av[argc_index++]);
		if (argc - 1 == 5)
			philo[philo_i].nbr_meals_per_philo = ft_atoi(av[argc_index]);
		philo[philo_i].id = philo_i;
		philo[philo_i].meals_eaten = 0;
		assign_forks(&philo[philo_i], philo->number_of_philos);
		philo_i++;
	}
	return (philo);
}
