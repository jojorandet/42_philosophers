/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 17:46:40 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int msg(char *help_msg, char *detail, int exit_no)
{
	if (detail != NULL)
		printf(help_msg, STR_PROGRAM_NAME, detail);
	else
		printf(help_msg, STR_PROGRAM_NAME);
	return (exit_no);
}

bool sim_has_stopped(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->sim_running_lock);
	if (philo->main->sim_is_running == false)
	{
		pthread_mutex_unlock(&philo->main->sim_running_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->main->sim_running_lock);
	return (false);
}

void destroy_mutexes(t_main *main)
{
	int i;

	i = 0;
	if (main)
	{
		if (main->fork_array)
		{
			while (i < main->params.nb_philos)
			{
				pthread_mutex_destroy(&main->fork_array[i]);
				pthread_mutex_destroy(&main->philo[i].last_meal_lock);
				pthread_mutex_destroy(&main->philo[i].is_full_lock);
				pthread_mutex_destroy(&main->philo[i].meals_eaten_lock);
				i++;
			}
			free(main->fork_array);
			main->fork_array = NULL;
		}
		pthread_mutex_destroy(&main->write_lock);
		pthread_mutex_destroy(&main->sim_running_lock);
	}
}

void free_all_resources(t_main *main)
{
	destroy_mutexes(main);
	if (main->philo)
	{
		free(main->philo);
		main->philo = NULL;
	}
}
