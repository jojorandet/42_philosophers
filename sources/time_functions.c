/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:26:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 13:34:24 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_current_time_in_miliseconds(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() failed.\n", 2);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(time_t time_limit_ms)
{
	time_t	start;

	start = get_current_time_in_miliseconds();
	while (get_current_time_in_miliseconds() - start < time_limit_ms)
		usleep(500);
	return (0);
}
