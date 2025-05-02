/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/01 18:45:20 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

unsigned long calculate_time_difference(struct timeval *start, struct timeval *end)
{
	unsigned long	time_elapsed;
	unsigned long	start_microsecond;
	unsigned long	end_microsecond;

	start_microsecond = start->tv_sec * 1000000UL;
	end_microsecond = end->tv_sec * 1000000UL;
	time_elapsed = (end_microsecond + end->tv_usec) - (start_microsecond + start->tv_usec);
	return (time_elapsed);
}

void	init_philo(t_philo *philo)
{
	
}

int	main(int argc, char **argv)
{
	struct timeval	end;
	unsigned long	time_elapsed;

	t_philo	philo;
	(void)argc;
	(void)argv;
	init_philo(&philo);
	for(int i = 0; i < 1e5; i++){
	}
	gettimeofday(&end, NULL);
	time_elapsed = calculate_time_difference(&start, &end);
	printf("time taken to count to 10^5 is %ld microseconds.\n",time_elapsed);
	return (0);
}