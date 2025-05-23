/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:26:17 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/23 15:16:54 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_t_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() failed.\n", 2);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(time_t time_limit_ms)
{
	time_t	start;

	start = get_t_in_ms();
	while (get_t_in_ms() - start < time_limit_ms)
		usleep(500);
	return (0);
}
