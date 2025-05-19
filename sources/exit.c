/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/19 17:07:22 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg(char *help_msg, char *detail, int exit_no)
{
	if (detail != NULL)
	{
		printf(help_msg, STR_PROGRAM_NAME, detail);
	}
	else
	{
		printf(help_msg, STR_PROGRAM_NAME);
	}
	return (exit_no);
}

void	destroy_mutexes(t_table *table)
{
	int i = 0;
	
	if (table->fork_mutexes)
	{
		while (i < table->number_of_philos)
		{
			pthread_mutex_destroy(&table->fork_mutexes[i]);
			i++;
		}
		free(table->fork_mutexes);
		table->fork_mutexes = NULL;
	}
}

void	exit_philo(t_table *table)
{
	free(table->philo);
}
