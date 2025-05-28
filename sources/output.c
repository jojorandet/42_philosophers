/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/28 11:51:14 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo_data *philo, char *action)
{
	printf("Timestamp %ld ms: Philo %ld %s", get_time_in_ms(), \
		philo->id, action);
}

static void	match_output_to_status(t_philo_data *philo, t_philo_state state)
{
	pthread_mutex_lock(&philo->global->write_lock);
	if (state == EATING)
	{
		print_status(philo, " is eating\n");
	}
	else if (state == SLEEPING)
	{
		print_status(philo, " is sleeping\n");
	}
	else if (state == THINKING)
	{
		print_status(philo, " is thinking\n");
	}
	else if (state == GOT_FIRST_FORK || state == GOT_SECOND_FORK)
	{
		print_status (philo, " has taken a fork\n");
	}
	else
	{
		print_status(philo, " died\n");
	}
	pthread_mutex_unlock(&philo->global->write_lock);
}

void	*log_philo_status(t_philo_data *philo, t_philo_state state)
{
	if (check_if_sim_stopped(philo))
		return (NULL);
	match_output_to_status(philo, state);
}
