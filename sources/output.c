/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 12:40:52 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo_data *philo, char *action)
{
	printf("Philo %ld %s", philo->id, action);
}

void	*log_philo_status(void	*data)
{
	t_philo_data *philo;

	philo = (t_philo_data *)data;
	pthread_mutex_lock(&philo->global->write_lock);
	// if (state == EATING)
	// {
	// 	print_status(global->philo, " is eating\n");
	// }
	// else if(state == SLEEPING)
	// {
	// 	print_status(global->philo, " is sleeping\n");
	// }
	// else if(state == THINKING)
	// {
	// 	print_status(global->philo, " is thinking\n");
	// }
	// else if(state == GOT_FIRST_FORK || state == GOT_SECOND_FORK)
	// {
	// 	print_status(global->philo, " has taken a fork\sn");  
	// }
	// else
	// {
	// 	print_status(global->philo, " died\n");
	// }
	print_status(philo, "is doing someting\n");
	pthread_mutex_unlock(&philo->global->write_lock);
	return (NULL); //temporary for the function to work
}


//i need the time in ms with the philo start time 