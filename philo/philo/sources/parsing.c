/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:15 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/12 17:13:15 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_a_number(char *s)
{
	while (*s == '-')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
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
	int		len;
	char	*int_max;
	int		len_max;

	int_max = "2147483647";
	len_max = ft_strlen(int_max);
	len = ft_strlen(s);
	if (len > len_max)
		return (1);
	if (len < len_max)
		return (0);
	return (ft_strcmp(s, int_max) > 0);
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
		if (is_int_max(argv[i]))
			return (msg(STR_INT_TOO_BIG, argv[i], EXIT_FAILURE), false);
		nb = ft_atoi(argv[i]);
		if (i == 1 && nb > MAX_PHILO)
			return (msg(STR_TOO_MANY_THREADS, argv[i], EXIT_FAILURE), false);
		if (i == 1 && nb <= 0)
			return (msg(STR_NEGATIVE_INPUT, argv[i], EXIT_FAILURE), false);
		i++;
	}
	return (true);
}
