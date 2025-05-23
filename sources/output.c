/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/23 11:05:36 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo_data *philo, char *action)
{
	printf("Philo %d %s", philo->id, action);
}

void	log_philo_status(t_global_data *global, t_philo_state state)
{
	pthread_mutex_lock(&global->write_lock);
	if (state == EATING)
	{
		print_status(global->philo, " is eating\n");
	}
	else if(state == SLEEPING)
	{
		print_status(global->philo, " is sleeping\n");
	}
	else if(state == THINKING)
	{
		print_status(global->philo, " is thinking\n");
	}
	else if(state == GOT_FIRST_FORK || state == GOT_SECOND_FORK)
	{
		print_status(global->philo, " has taken a fork\n");  
	}
	else
	{
		print_status(global->philo, " died\n");
	}
	pthread_mutex_unlock(&global->write_lock);
}


//i need the time in ms with the philo start time 