/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:26:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/19 17:59:24 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo_sleep(t_table *table, time_t time_to_rest)
{
	time_t	end_of_rest_time;

	end_of_rest_time = get_time_in_miliseconds() + time_to_rest;
	while (get_time_in_miliseconds() < end_of_rest_time)
	{
		
	}
}


time_t	get_time_in_miliseconds(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}