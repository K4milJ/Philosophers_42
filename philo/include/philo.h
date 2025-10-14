/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:45 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/14 18:32:11 by kjamrosz         ###   ########.fr       */
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

#define DEBUG_MODE 0

typedef struct	s_table t_table;

// typedef enum e_action
// {
// 	GET,
// 	SET
// }	t_action;


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
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

typedef struct	s_table
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	bool			is_end_of_simulation;
	bool			philos_ready;
	long			simulation_start;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	print_mutex;
}	t_table;

/* CLEANUP & EXIT*/
void error_exit(char *msg);

/* INPUT */
// void input_check_and_init(t_table *table, char **argv);
void data_init(t_table *table);
void parsing(t_table *table, char **argv);

/* DINNER */
void	start_the_dinner(t_table *table);

/* UTILS FUNC */
int	gettime(t_timecode timecode);
void precise_usleep(long usec, t_table *table);

/* UTILS_SIM */
// bool	manage_bool(pthread_mutex_t *mutex, bool *dest, bool val, t_action action);
// long	manage_long(pthread_mutex_t *mutex, long *dest, long val, t_action action);
void	set_long(pthread_mutex_t *mutex, long *dest, long src);
long	get_long(pthread_mutex_t *mutex, bool *val);
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool src);
bool	get_bool(pthread_mutex_t *mutex, bool *val);
bool	dinner_finished(t_table *table);

/* SYNCHRONIZATION */
void	ft_spinlock(t_table *table);

/* PRINT */
void	print_status(t_philo_status status, t_philo *philo, bool debug);

/* FT_ATOL */
long	ft_atol(const char *str);

/* SAFE FUNCTIONS */
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(pthread_mutex_t *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);

