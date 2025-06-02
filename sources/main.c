/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/02 10:59:41 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_param(int argc, char **argv, t_param *param)
{
	param->nb_philos = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	param->nbr_meals_per_philo = -1;
	if (argc - 1 == 5)
		param->nbr_meals_per_philo = ft_atoi(argv[5]);
}

/**
 * 
 * This program explores concurent programing around the dining philosopher 
 * problem. 
 * A good method is to determine which sections of the code are critical, and
 * to protect them with locks. These locks are called mutexes which 
 * stands for mutual exclusion.\
 * @brief see .h file for details about the structures
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
	if (!(init_global_struct(&global, &params)))
		return (EXIT_FAILURE);
	global.philo = init_thread_data(&global);
	if (!global.philo)
		return (EXIT_FAILURE);
	start_philo_routine(&global);
	finish_philo_routine(&global);
	exit_philo(&global);
	return (EXIT_SUCCESS);
}
