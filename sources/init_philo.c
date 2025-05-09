/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/09 17:19:32 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
*	Trick to avoid a deadlock where all philosophers grab their right fork
*	and never end up having a left fork to grab, we made uneven philo->id 
	philos right handed and even philos left handed.
*	- 
*	
*	
*/
static void	assign_forks(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		philo->fork[0] = philo->id;
		philo->fork[1] = (philo->id + 1) % (philo->table->number_of_philos);
	}
	else
	{
		philo->fork[0] = (philo->id + 1) % (philo->table->number_of_philos);
		philo->fork[1] = philo->id;
	}
}

/*
*	- philo is an array of structures (each structure is one philo)
*	- when accessing philo[i] im directly accessing the structure of philo i
*	- this is to pepare for pthread_create which passes args (struct)
*	- philo  has_eaten will let me know if he's eaten or not for the grim 
*	reaper
*	- all philosophers, regardless of their count, point to the same original
*	 data structure.
*/
static t_philo	*init_philo_array(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->number_of_philos);
	while (i < table->number_of_philos)
	{
		philo[i].id = i;
		philo[i].has_eaten = 0;
		philo[i].table = table;
		assign_forks(&philo[i]);
		i++;
	}
	return (philo);
}

/*
*	initialise the core structure with the input of the user
*	- number of philos is an int, cannot be negative. edge case with 1 philo
*	- number of forks = number of philos
*	- time to die in miliseconds: if philo has not eaten within time to die ms
*	they die.
*	- time to eat time it takes to eat, philo must have 2 forks to eat
*	time_to_sleep in miliseconds, will be sent to custom ft_usleep in utils.c
*/
t_table	*init_philo(int argc, char **argv, t_table *table)
{
	int	i;

	i = 1;
	table->number_of_philos = ft_atoi(argv[i++]);
	table->time_to_die = ft_atoi(argv[i++]);
	table->time_to_eat = ft_atoi(argv[i++]);
	table->time_to_sleep = ft_atoi(argv[i++]);
	table->philo = init_philo_array(table);
	if (argc - 1 == 5)
		table->nbr_of_times_philo_must_eat = ft_atoi(argv[i++]);
	init_philo_array(table);
	return (table);
}
