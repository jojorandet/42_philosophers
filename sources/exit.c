/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 12:50:16 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msg(char *help_msg, char *detail, int exit_no)
{
	if (detail != NULL)
		printf(help_msg, STR_PROGRAM_NAME, detail);
	else
		printf(help_msg, STR_PROGRAM_NAME);
	return (exit_no);
}

bool	sim_has_stopped(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->global->sim_end_lock);
	if (philo->global->sim_has_ended == true)
	{
		pthread_mutex_unlock(&philo->global->sim_end_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->global->sim_end_lock);
	return (false);
}

void	destroy_mutexes(t_global_data *global)
{
	int	i;

	i = 1;
	if (global->fork_array)
	{
		while (i <= global->params.nb_philos)
		{
			pthread_mutex_destroy(&global->fork_array[i]);
			i++;
		}
		free(global->fork_array);
		global->fork_array = NULL;
	}
	pthread_mutex_destroy(&global->write_lock);
	pthread_mutex_destroy(&global->sim_end_lock);
}

void	exit_philo(t_global_data *global)
{
	destroy_mutexes(global);
	if (global->philo)
	{
		free(global->philo);
		global->philo = NULL;
	}
}
