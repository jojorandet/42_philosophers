/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:15 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/08 14:22:06 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_a_number(char *s)
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
	return (result);
}

int	is_int_max(char *s)
{
	if (ft_strlen(s) == 11 && (ft_strcmp(s, "2147483647") == 0))
		return (0);
	else
		return (1);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 1;
	while (i < argc)
	{
		if (!is_a_number(argv[i]))
			return (msg(STR_NOT_NUM, NULL, EXIT_FAILURE), false);
		if (!is_int_max(argv[i]))
			return (msg(STR_INT_TOO_BIG, argv[i], EXIT_FAILURE));
		nb = ft_atoi(argv[i]);
		if (argc == 1 && nb > MAX_PHILO)
			return (msg(STR_TOO_MANY_THREADS, argv[i], EXIT_FAILURE));
		if (argc == 1 && nb <= 0)
			return (msg(STR_TOO_MANY_THREADS, argv[i], EXIT_FAILURE));
		i++;
	}
	printf("all arguments pass\n");
	return (true);
}
