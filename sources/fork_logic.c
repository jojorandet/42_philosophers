/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:46:07 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/04 14:52:44 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * when the philo is waiting to eat, he is thinking.
 * 
 */
void	assign_forks(t_philo *p,  pthread_mutex_t **ff, pthread_mutex_t **sf)
{
	int	left_id;
	int	right_id;
	
	left_id = p->id;
	right_id = (p->id + 1) % p->main->params.nb_philos;
	if (left_id < right_id)
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

int	wait_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	assign_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	if (!log_philo_status(philo, GOT_FIRST_FORK))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	if (!log_philo_status(philo, GOT_SECOND_FORK))
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (0);
	}
	return (1);
}
