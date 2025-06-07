/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:46:07 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 15:41:55 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * when the philo is waiting to eat, he is thinking.
 *
 */
void assign_forks(t_philo *p, pthread_mutex_t **ff, pthread_mutex_t **sf)
{
	
	if ((p->id % 2) == 0)
	{
		*ff = p->left_fork;
		*sf = p->right_fork;
	}
	else
	{
		*ff = p->right_fork;
		*sf = p->left_fork;
	}
}

int wait_forks(t_philo *philo, pthread_mutex_t **ff, pthread_mutex_t **sf)
{

	assign_forks(philo, ff, sf);
	pthread_mutex_lock(*ff);
	if (!log_philo_status(philo, GOT_FIRST_FORK))
	{
		pthread_mutex_unlock(*ff);
		return (0);
	}
	pthread_mutex_lock(*sf);
	if (!log_philo_status(philo, GOT_SECOND_FORK))
	{
		pthread_mutex_unlock(*sf);
		pthread_mutex_unlock(*ff);
		return (0);
	}
	return (1);
}
