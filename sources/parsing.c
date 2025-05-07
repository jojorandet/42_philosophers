/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:08:15 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/07 18:40:19 by jrandet          ###   ########.fr       */
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
	while (*s)
	{

	}
}

int	is_valid_input(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!is_a_number(argv[i]))
			return (msg(STR_NOT_NUM, EXIT_FAILURE), false);
		
		i++;
	}
	printf("all arguments pass\n");
	return (true);
}


//what are some edge cases i need to look out for?
// is the input a digit or not? first check before doing anything 