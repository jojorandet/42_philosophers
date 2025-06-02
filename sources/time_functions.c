/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:26:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 16:40:45 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @param time is a a variable of type time_t which is a built in struct
 * for the gettimeofday function.abort
 * @param time.tv_sec is in seconds, so to get in miliseconds * by 1000
 * @param time.tv_usec is in microseconds, so divided by 1000.
 * @param result is a value of type time_t used in function below.
 * result is in miliseconds for the simualtion
 * f can be called separately to the ft_usleep function for timestamp
 */
long long	get_time_in_ms(void)
{
	struct timeval	time;
	long long		result;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() failed.\n", 2);
	result = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	//printf("%lld (result of get time in ms\n)", result);
	return (result);
}

/**
 * usleep (1000) may sleep 800us or 1200 us depending on the system
 * Linux and Macos behave differently for the usleep, leading to 
 * inconcistencies
 * Instead of relying on the system's end alarm system, I build my own
 */
int	ft_usleep(time_t time_limit_us)
{
	time_t	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time_limit_us)
		usleep(500);
	return (0);
}
