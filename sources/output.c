/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/12 13:43:16 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *action)
{
	long long	time;
	int	philo_i = 0;

	time = get_time_in_ms() - philo->main->start_time;
	printf("%6lld ms: Philo %d", time, philo->id);
	if (philo->main->params.nb_philos < 20)
	{
		while (philo_i < philo->id)
		{
			printf("   ");
			philo_i++;
		}
	}
	printf("%s", action);
}

bool	log_philo_status(t_philo *philo, t_philo_state state)
{
	pthread_mutex_lock(philo->write_lock);
	if (sim_has_stopped(philo))
	{
		pthread_mutex_unlock(philo->write_lock);
		return (false);
	}
	if (state == THINKING)
		print_status(philo, " 💭\n");
	else if (state == GOT_FIRST_FORK)
		print_status(philo, " 🥄 \n");
	else if (state == GOT_SECOND_FORK)
		print_status(philo, " 🥄 \n");
	else if (state == EATING)
		print_status(philo, " 🍽️ \n");
	else if (state == SLEEPING)
		print_status(philo, " 😴 \n");
	else
		print_status(philo, " ☠️ \n");
	pthread_mutex_unlock(philo->write_lock);
	return (true);
}

// /**
//  * @brief made the choice to have the get_time_in_ms at time of print for now
//  * subject to change later on.
//  */
// static void	print_status(t_philo *philo, char *action)
// {
// 	long long	time;

// 	time = get_time_in_ms() - philo->main->start_time;
// 	printf("%6lld ms: Philo %d %s", time, philo->id, action);
// }

// bool	log_philo_status(t_philo *philo, t_philo_state state)
// {
// 	pthread_mutex_lock(philo->write_lock);
// 	if (sim_has_stopped(philo))
// 	{
// 		pthread_mutex_unlock(philo->write_lock);
// 		return (false);
// 	}
// 	if (state == THINKING)
// 		print_status(philo, " is thinking\n");
// 	else if (state == GOT_FIRST_FORK)
// 		print_status(philo, " has taken a fork\n");
// 	else if (state == GOT_SECOND_FORK)
// 		print_status(philo, " has taken a fork\n");
// 	else if (state == EATING)
// 		print_status(philo, " is eating\n");
// 	else if (state == SLEEPING)
// 		print_status(philo, " is sleeping\n");
// 	else
// 		print_status(philo, " died\n");
// 	pthread_mutex_unlock(philo->write_lock);
// 	return (true);
// }
