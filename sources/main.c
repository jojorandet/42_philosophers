/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/26 19:15:20 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 
 * This program explores concurent programing around the dining philosopher 
 * problem. 
 * A good method is to determine which sections of the code are critical, and
 * to protect them with locks. 
 */
int	main(int argc, char **argv)
{
	t_global_data	global;
	t_param			params;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(STR_HELP, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	init_param(argc, argv, &params);
	init_global_struct(&global, &params);
	global.philo =  init_thread_data(&global);
	if (!global.philo)
		return (EXIT_FAILURE);
	start_philo_routine(&global);
	finish_philo_routine(&global);
	exit_philo(&global);
	return (EXIT_SUCCESS);
}
