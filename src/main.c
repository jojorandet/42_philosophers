/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/01 14:21:10 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"


unsigned long	calculate_elapsed_time(void)
{
	struct	timeval	start;
	struct	timeval	end;
	unsigned long	elapsed_usec;	

	gettimeofday(&start, 0);
	sleep(1);
	gettimeofday(&end, 0);
	elapsed_usec = ((end.tv_sec * 1e6) + end.tv_usec) - ((start.tv_sec * 1e6) + start.tv_usec);
	return (elapsed_usec);
}

int main(int argc, char **argv)
{

	(void)argc;
	//if (argc != 6)
		//return (1);
	(void)argv;
	printf("Philosophers has started...\n\n");
	printf("%lu Philosopher 1 has taken a fork\n", calculate_elapsed_time());
	printf("%lu Philosopher 1 has taken a fork\n", calculate_elapsed_time());
	printf("%lu Philosopher 1 is eating\n", calculate_elapsed_time());
	printf("%lu Philosopher 1 is sleeping\n", calculate_elapsed_time());
	printf("%lu Philosopher 1 had died\n", calculate_elapsed_time());

	return (0);
}

//everytime i will print, i need to get the time elapsed since that point in time 