/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:05:44 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/12 13:26:45 by jrandet          ###   ########.fr       */
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
static void	initialise_forks(t_philo *philo, int n_philos)
{
	int	left_fork_index;
	int	right_fork_index;

	left_fork_index = philo->id;
	right_fork_index = (philo->id + 1) % n_philos;
	philo->left_fork = philo->main->fork_array + left_fork_index;
	philo->right_fork = philo->main->fork_array + right_fork_index;
	philo->right_fork = philo->main->fork_array + right_fork_index;
}

/**
 * Table of threads, useful for the monitor to traverse and see which
 * philo needs to be taken care of.
 *
 * @return is the pointer to the array of philo structures.
 */
t_philo	*init_thread_data(t_main *main)
{
	t_philo	*philo;
	int		philo_i;

	philo = malloc(sizeof(t_philo) * main->params.nb_philos);
	if (!philo)
	{
		ft_putstr_fd("Error: Malloc.", 2);
		free_all_resources(main);
		return (NULL);
	}
	philo_i = 0;
	while (philo_i < main->params.nb_philos)
	{
		philo[philo_i].id = philo_i;
		philo[philo_i].meals_eaten = 0;
		philo[philo_i].last_meal = main->start_time;
		philo[philo_i].main = main;
		philo[philo_i].is_full = false;
		philo[philo_i].write_lock = &philo[philo_i].main->write_lock;
		initialise_forks(&philo[philo_i], main->params.nb_philos);
		pthread_mutex_init(&philo[philo_i].last_meal_lock, NULL);
		pthread_mutex_init(&philo[philo_i].is_full_lock, NULL);
		philo_i++;
	}
	return (philo);
}
