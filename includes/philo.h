/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:45:01 by jrandet           #+#    #+#             */
/*   Updated: 2025/06/07 15:42:10 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

/******************************** INCLUDES ***********************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_PHILO 200
#define STR_PROGRAM_NAME "./philo"
#define STR_HELP "Input error: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep]"
#define STR_NOT_NUM " %s: Input must be of type int. Must be between 0 and \
INT_MAX"
#define STR_INT_TOO_BIG "%s: Input %s above int_max, please give valid input."
#define STR_TOO_MANY_THREADS "%s: Exceeded the maximum amount of philosophers \
for optimal performance, please give <number_of_philosophes> <= %s"
#define STR_NEGATIVE_INPUT "%s: Input %s is negative, philosophers can only be \
positive :-)"
#define MALLOC_ERROR "Error: could not malloc, not enough space available."

/******************************** STRUCTURES *******************************/

typedef struct s_main t_main;

/**
 * @param Parameters are the parameters given to launch the phoilosopher simulation
 *
 * @note all the time values are given in miliseconds.
 */
typedef enum e_philo_state
{
	DIED,
	EATING,
	SLEEPING,
	THINKING,
	GOT_FIRST_FORK,
	GOT_SECOND_FORK
} t_philo_state;

typedef struct s_param
{
	int nb_philos;
	long long time_to_die;
	long long time_to_eat;
	long long time_to_sleep;
	int nbr_meals_per_philo;
} t_param;

/**
 * @brief data structure representing an individual philosopher.
 * @param param a complete structure with the philosopher simulation parameters.
 * @param id each philosopher's unique identifier.
 * @param thread required for pthread_create function
 * @param meals_eaten Number of meals eaten by Philosopher.
 * @param fork fork access for each philo. fork[0] is the first fork taken, fork[1]
 * the second.
 * @param write_lock Pointer to shared mutex used for controlled output synchronization.
 * I didnt want to give the pointer to main, so i give pointers to one shared
 * mutex memory space.
 */
typedef struct s_philo_data
{
	int id;
	pthread_t thread;
	int meals_eaten;
	int fork[2];
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_philo_state state;
	long long last_meal;
	pthread_mutex_t last_meal_lock;
	pthread_mutex_t start_simu;
	pthread_mutex_t is_done_lock;
	t_main *main;
} t_philo;

/**
 * @param fork_mutexes Array of mutexes for all forks.
 * @param write_lock  mutex for preventing data races on output functions.
 * @param philo_is_dead is a flag indicating the end of the simulation.
 * @param philo pointer to the philo structures.
 * @
 */
typedef struct s_main
{
	long long start_time;
	pthread_t watch_thread;
	t_param params;
	bool sim_is_running; // needs mutex
	pthread_mutex_t *fork_array;
	pthread_mutex_t write_lock;
	pthread_mutex_t sim_running_lock;
	t_philo *philo;
} t_main;

/******************************* FUNCTIONS *********************************/

int main(int argc, char **argv);
int msg(char *help_msg, char *detail, int exit_no);

int is_valid_input(int argc, char **argv);
int is_int_max(char *s);
int ft_atoi(char *s);

void init_param(int argc, char **argv, t_param *param);

t_philo *init_thread_data(t_main *main);
bool init_main_struct(t_main *main, t_param *params);

int wait_forks(t_philo *philo, pthread_mutex_t **ff, pthread_mutex_t **sf);
void assign_forks(t_philo *p, pthread_mutex_t **ff, pthread_mutex_t **sf);
int start_philo_routine(t_main *table);
void *routine(void *data);
bool log_philo_status(t_philo *philo, t_philo_state state);
void finish_philo_routine(t_main *main);

void *watch_rounds(void *data);

int ft_usleep(time_t time_limit_us);
int ft_strlen(char *s);
int ft_strcmp(char *s1, char *s2);
void ft_putstr_fd(char *s, int fd);
char *ft_strcpy(char *src, char *dst);
long long get_time_in_ms(void);

void destroy_mutexes(t_main *table);
bool sim_has_stopped(t_philo *philo);
void free_all_resources(t_main *main);

#endif