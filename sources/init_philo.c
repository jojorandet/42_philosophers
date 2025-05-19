/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/19 17:47:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*init_fork_mutex(t_table *table)
{
	pthread_mutex_t	*fork_mutexes;
	int				i;

	i = 0;
	fork_mutexes = malloc(sizeof(pthread_mutex_t) * table->number_of_philos);
	while (i < table->number_of_philos)
	{
		pthread_mutex_init(&fork_mutexes[i], 0);
		printf("the mutex is initialised for fork number %d\n", i);
		i++;
	}
	return (fork_mutexes);
}

/*
*	here we are initialising all the mutexes for the exercise
*	
*/
static bool	init_all_mutexes(t_table *table)
{
	table->fork_mutexes = init_fork_mutex(table);
	return (true);
}

/*
*	Trick to avoid a deadlock where all philosophers grab their right fork
*	and never end up having a left fork to grab, we made uneven philo->id 
	philos right handed and even philos left handed.
*	- the forks are positionned like this: L(id)  PHILO(id)  R(id + 1)
*	- uneven philo will first grab the fork on their right (id + 1)
*	- uneven philo will then grab the fork on their left (id) when it is free. 
*	- fork will be represented by a mutex in this specific scenario.
*/
static void	assign_forks(t_philo *philo)
{
	if ((philo->id % 2) == 0) 
	{
		philo->fork[0] = (philo->id + 1) % (philo->table->number_of_philos); // right handed if not pair (philo 1 starts )
		philo->fork[1] = philo->id; // he then takes the fork om his 
	}
	else
	{
		philo->fork[0] = philo->id; // the philo 
		philo->fork[1] = (philo->id + 1) % (philo->table->number_of_philos); //philo is right handed 
	}
	printf("philo number %ld will first grab fork %d and then fork %d\n", philo->id, philo->fork[0], philo->fork[1]);
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
	printf("the nunber of philos is %d\n", table->number_of_philos);
	philo = malloc(sizeof(t_philo) * table->number_of_philos);
	while (i < table->number_of_philos) // loop through the number of pholosophers 
	{
		philo[i].id = i; //[philo id starts at 0]
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
	if (!init_all_mutexes(table))
		return (NULL);
	return (table);
}
