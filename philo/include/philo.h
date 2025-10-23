/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:45 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/23 14:40:42 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

typedef struct s_table	t_table;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef enum e_timecode
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_timecode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_1_FORK,
	TAKE_2_FORK,
	DIED
}	t_philo_status;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				philo_id;
	long			meal_count;
	bool			is_full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	bool			is_end_of_simulation;
	bool			philos_ready;
	long			simulation_start;
	long			running_philos_num;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
}	t_table;

/* DINNER */
void	start_the_dinner(t_table *table);
void	thinking(t_philo *philo, bool before_sim);

/* FT_ATOL */
long	ft_atol(const char *str);

/* INPUT */
void	input_check_and_init(t_table *table, char **argv);
void	data_init(t_table *table);
void	parsing(t_table *table, char **argv);

/* MONITORING */
void	*dinner_monitor(void *input);

/* PRINT */
void	print_status(t_philo_status status, t_philo *philo);

/* SAFE FUNCTIONS */
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
			t_opcode opcode);

/* SYNCHRONIZATION */
void	ft_spinlock(t_table *table);
bool	all_philos_running(pthread_mutex_t *mutex, long *running_philos_num,
			long philo_num);
void	desync_philos(t_philo *philo);

/* UTILS FUNC */
void	clean_exit(t_table *table);
void	error_exit(char *msg);
long	gettime(t_timecode timecode);
void	precise_usleep(long usec, t_table *table);

/* UTILS_SIM */
void	set_long(pthread_mutex_t *mutex, long *dest, long src);
long	get_long(pthread_mutex_t *mutex, long *val);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool src);
bool	get_bool(pthread_mutex_t *mutex, bool *val);
bool	dinner_finished(t_table *table);
