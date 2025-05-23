/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/23 14:44:49 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global_data	global;
	t_param			params;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(STR_HELP, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	init_param(argc, argv, &params);
	global.philo =  init_thread_data(&global, &params);
	initialise_global_mutexes(&global);
	if (!global.philo)
		return (EXIT_FAILURE);
	start_philo_routine(&global);
	finish_philo_routine(&global);
	exit_philo(&global);
	return (EXIT_SUCCESS);
}
