/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:50:59 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 16:15:53 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo_data *philo, char *action)
{
	
}

void	log_philo_status(t_global_data *global, t_philo_state state)
{
	pthread_mutex_lock(&global->write_lock);
	if (state == EATING)
	{
		print_status()
	}
	pthread_mutex_unlock(&global->write_lock);
}