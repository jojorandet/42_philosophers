/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonasvoisard <jonasvoisard@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:26:28 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/05 12:18:42 by jonasvoisar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	return (s1 - s2);
}

void ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char *ft_strcpy(char *src, char *dst)
{
	char *start;

	start = dst;
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
	return (start);
}
