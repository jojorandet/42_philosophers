/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 21:46:36 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief made the choice to have the get_time_in_ms at time of print for now
 * subject to change later on.
 */
static void print_status(t_philo *philo, char *action)
{
	long long time;
	int philo_i;

	time = get_time_in_ms() - philo->main->start_time;
	printf("%6.lld ms: Philo %d", time, philo->id);
	philo_i = 0;
	while (philo_i <= philo->id)
	{
		printf("   ");
		philo_i++;
	}
	printf("%s", action);
}

static void match_output_to_status(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(&philo->main->write_lock);
	if (state == THINKING)
		print_status(philo, " 💭 \n");
	else if (state == GOT_FIRST_FORK)
		print_status(philo, " 🥄 \n");
	else if (state == GOT_SECOND_FORK)
		print_status(philo, " 🥄 \n");
	else if (state == EATING)
		print_status(philo, " 🍽️ \n");
	else if (state == SLEEPING)
		print_status(philo, " 😴 \n");
	else if (state == HEY)
		print_status(philo, " HEY \n");
	else
		print_status(philo, " ☠️ \n");
	pthread_mutex_unlock(&philo->main->write_lock);
}

bool log_philo_status(t_philo *philo, t_philo_state state)
{
	if (sim_has_stopped(philo))
		return (false);
	match_output_to_status(philo, state);
	return (true);
}
