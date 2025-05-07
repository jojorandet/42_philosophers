/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:53:00 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/07 19:14:54 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int msg(char *help_msg, char *detail, int exit_no)
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
