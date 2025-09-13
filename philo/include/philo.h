/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:45 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/09/13 13:50:46 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct	s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct	s_philo
{
	int				philo_id;
	long			meal_count;
	bool			is_full;
	t_fork			*first_fork;
	t_fork			*second_fork;
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
}	t_table;