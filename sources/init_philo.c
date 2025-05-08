/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/08 17:26:16 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo *init_philo_array(t_table *table)
{
	t_philo *philo;

	int i = 0;

	philo = malloc(sizeof(t_philo) * table->number_of_philos);
	while (i < table->number_of_philos)
	{
		philo[i].philo_id = i;
		philo[i].right_fork = pthread_mutex_init(&)
		i++;
	}
	
}


/*
*	initialise the core structure with the input
*	
*/
t_table	*init_philo(int argc, char **argv, t_table *table)
{
	int i;

	i = 1;
	table = malloc(sizeof(t_table) * 1);
	memset(table, 0, sizeof(t_table));
	table->number_of_philos = ft_atoi(argv[i++]);
	table->time_to_die = ft_atoi(argv[i++]);
	table->time_to_eat = ft_atoi(argv[i++]);
	table->time_to_sleep = ft_atoi(argv[i++]);
	if (argc - 1 == 5)
	{
		table->nbr_of_times_philo_must_eat = ft_atoi(argv[i++]);
		printf("last one is worth %d\n", table->nbr_of_times_philo_must_eat);
	}
	table->philo = init_philo_array(table);
	return (table);
}
