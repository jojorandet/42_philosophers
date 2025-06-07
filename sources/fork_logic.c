/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:46:07 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 21:17:38 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * I used a classic pair vs unpair philosopher id methodology. 
 * The key challenge I observed while coding was that I used to then 
 * manipulate the left fork and right fork in the main routine, but this
 * did not take into account the first fork second fork ordering. 
 * In all cases, it was with the order of the forks i needed to work
 * with, and not the left fork and right fork as their order
 * varies according to the philosopher.
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
/**
 * In this function, I assign the forks, and then I unlock the 
 * mutexes one by one. The mutexes are not the forks themselves, 
 * but rather there is a fork around the
 */
int grab_forks(t_philo *philo, pthread_mutex_t **ff, pthread_mutex_t **sf)
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
