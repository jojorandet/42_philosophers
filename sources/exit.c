/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 14:34:57 by jrandet          ###   ########.fr       */
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

void	destroy_mutexes(t_global_data *global)
{
	int	i;

	i = 0;
	if (global->fork_mutexes)
	{
		while (i < global->philo->number_of_philos)
		{
			pthread_mutex_destroy(&global->fork_mutexes[i]);
			i++;
		}
		free(global->fork_mutexes);
		global->fork_mutexes = NULL;
	}
}

void	exit_philo(t_global_data *global)
{
	free(global->philo);
}
