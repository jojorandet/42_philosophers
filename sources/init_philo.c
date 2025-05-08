/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:24:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/08 14:41:33 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table_philo	*init_philo(int argc, char **argv, t_philo *philo)
{
	t_table_philo *table;
	int i;

	(void)philo;
	i = 1;
	table = malloc(sizeof(t_table_philo) * 1);
	memset(table, 0, sizeof(t_table_philo));
	table->number_of_philosophers = ft_atoi(argv[i++]);
	printf("number of philo is worth %d\n", table->number_of_philosophers);
	table->time_to_die = ft_atoi(argv[i++]);
	table->time_to_eat = ft_atoi(argv[i++]);
	printf("time to eat is worth %d\n", table->time_to_eat);
	table->time_to_sleep = ft_atoi(argv[i++]);
	if (argc - 1 == 5)
	{
		table->nbr_of_times_philo_must_eat = ft_atoi(argv[i++]);
		printf("last one is worth %d\n", table->nbr_of_times_philo_must_eat);
	}
	//table->philo = init_philo_array(argc, argv, philo);
	return (table);
}
