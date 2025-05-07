/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:15 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/07 19:07:09 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_a_number(char *s)
{
	while (*s)
	{
		if (*s >= '0' || *s <= '9')
			s++;
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	result;
	
	result = 0;
	while (*s && ('0' <= *s && *s <= '9'))
	{
		result = (result * 10) + (*s - '0');
		s++;
	}
	if (result > __INT_MAX__)
		return (-1);
	return (result);
}

int	is_valid_input(int argc, char **argv)
{
	int i;
	int nb;

	i = 1;
	while (i < argc)
	{
		if (!is_a_number(argv[i]))
			return (msg(STR_NOT_NUM, NULL, EXIT_FAILURE), false);
		nb = ft_atoi(argv[i]);
		if (nb == -1)
			return (msg(STR_INT_TOO_BIG, argv[i], EXIT_FAILURE));
		if (argc == 1 && nb > MAX_PHILO)
			return (msg(STR_TOO_MANY_THREADS, argv[i], EXIT_FAILURE));
		if (argc == 1 && nb <= 0)
			return (msg(STR_TOO_MANY_THREADS, argv[i], EXIT_FAILURE));
		i++;
	}
	printf("all arguments pass\n");
	return (true);
}


//what are some edge cases i need to look out for?
// is the input a digit or not? first check before doing anything 