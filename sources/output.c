/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/03 16:01:40 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief made the choice to have the get_time_in_ms at time of print for now
 * subject to change later on.
 */
static void	print_status(t_philo_data *philo, char *action)
{
	long long time;

	time = get_time_in_ms() - philo->main->start_time;
	printf("Timestamp %lld ms: Philo %d %s", time, philo->id, action);
}

static void	match_output_to_status(t_philo_data *philo, t_philo_state state)
{
	pthread_mutex_lock(&philo->main->write_lock);
	long long time;
	if (state == THINKING)
	{
		print_status(philo, " 				is thinking\n");
	}
	else if (state == GOT_FIRST_FORK)
	{
		time = get_time_in_ms() - philo->main->start_time;
		printf("Timestamp %lld ms: Philo %d has taken fork %d\n", time, philo->id, philo->fork[0]);
	}
		else if (state == GOT_SECOND_FORK)
	{
		time = get_time_in_ms() - philo->main->start_time;
		printf("Timestamp %lld ms: Philo %d has taken fork %d\n", time, philo->id, philo->fork[1]);
	}
	else if (state == EATING)
	{
		print_status(philo, " 					is eating\n");
	}
	else if (state == SLEEPING)
	{
		print_status(philo, " 						is sleeping\n");
	}
	else
	{
		print_status(philo, "	DEAD :-(\n");
	}
	pthread_mutex_unlock(&philo->main->write_lock);
}

bool	log_philo_status(t_philo_data *philo, t_philo_state state)
{
	if (sim_has_stopped(philo))
	{
		return (false);
	}
	match_output_to_status(philo, state);
	return (true);
}
