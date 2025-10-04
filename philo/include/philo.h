/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:45 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/04 18:49:32 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_table;

typedef enum e_action
{
	GET,
	SET
}	t_action;

/*fork is a mutex*/
typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

/*philo is a thread*/
typedef struct	s_philo
{
	int				philo_id;
	long			meal_count;
	bool			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_table			*table;
}	t_philo;

typedef struct	s_table
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	t_philo			*philos;
	t_fork			*forks;
	bool			is_end_of_simulation;
	bool			philos_ready;
	pthread_mutex_t	table_mutex;
	int				simulation_start;
}	t_table;

/* CLEANUP & EXIT*/
void error_exit(char *msg);

/* INPUT */
void input_check_and_init(t_table *table, char **argv);

/* UTILS */
int	gettime(void);
int	ft_atoi(const char *str);

/* DINNER */
void	start_the_dinner(t_table *table);

/* UTILS_SIM */
bool	manage_bool(pthread_mutex_t *mutex, bool *dest, bool val, t_action action);

/* SYNCHRONIZATION */
void	ft_spinlock(t_table *table);
