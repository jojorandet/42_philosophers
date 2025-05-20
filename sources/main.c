/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:42:34 by jrandet           #+#    #+#             */
/*   Updated: 2025/05/20 14:55:03 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global_data	global;
	int				number_of_philos;

	if (argc - 1 < 4 || argc - 1 > 5)
		return (msg(STR_HELP, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	number_of_philos = ft_atoi(argv[1]);
	global.philo = init_thread_data(argc, argv, number_of_philos);
	if (!global.philo)
		return (EXIT_FAILURE);
	if (!init_global_data(&global))
			return (EXIT_FAILURE);
	start_philo_routine(&global);
	finish_philo_routine(&global);
	exit_philo(&global);
	return (EXIT_SUCCESS);
}
