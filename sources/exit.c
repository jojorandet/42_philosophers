/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/08 16:02:20 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ptr_array(char ***array)
{
	char	***start;

	if (!array || !(*array))
		return ;
	start = array;
	while (**array)
	{
		free(**array);
		**array = NULL;
		array++;
	}
	free(*start);
	*start = NULL;
}

int	msg(char *help_msg, char *detail, int exit_no)
{
	if (detail != NULL)
	{
		printf(help_msg, STR_PROGRAM_NAME, detail);
	}
	else
	{
		printf(help_msg, STR_PROGRAM_NAME);
	}
	return (exit_no);
}

void	free_table_philo(t_table *table)
{
	free_ptr_array(&table->philo);
}