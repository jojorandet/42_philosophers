/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/30 19:54:13 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

int main(int argc, char **argv)
{
	struct	timeval tv;

	if (argc != 6)
		return (1);
	(void)argv;
	printf("hello\n");
	gettimeofday(&tv, NULL);
	printf("seconds since 1/1/1970: %lu\n", tv.tv_sec);
	printf("Microseconds: %lds\n", tv.tv_usec);
	return (0);
}
