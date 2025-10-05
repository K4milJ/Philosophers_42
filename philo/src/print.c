/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:53:25 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/05 11:18:47 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status_debug(t_philo_status status, t_philo *philo, long elapsed_time)
{
	if (status == TAKE_1_FORK && !dinner_finished(philo->table))
		printf("%ld %d has taken 1st fork\t%d", elapsed_time, philo->philo_id,
			philo->first_fork->fork_id);
	else if (status == TAKE_2_FORK && !dinner_finished(philo->table))
		printf("%ld %d has taken 2nd fork\t%d", elapsed_time, philo->philo_id,
			philo->second_fork->fork_id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf("%ld %d is eating\t%ld", elapsed_time, philo->philo_id, philo->meal_count);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf("%ld %d is sleeping", elapsed_time, philo->philo_id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf("%ld %d is thinking", elapsed_time, philo->philo_id);
	else if (status == DIED && !dinner_finished(philo->table))
		printf("%ld %d died", elapsed_time, philo->philo_id);
}

void	print_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed_time;

	elapsed_time = gettime(MILLISECOND) - philo->table->simulation_start;
	pthread_mutex_lock(&philo->table->print_mutex);
	if (debug)
		print_status_debug(status, philo, elapsed_time);
	else
	{
		if ((status == TAKE_1_FORK || status == TAKE_2_FORK)
			&& !dinner_finished(philo->table))
			printf("%ld %d has taken a fork", elapsed_time, philo->philo_id);
		else if (status == EATING && !dinner_finished(philo->table))
			printf("%ld %d is eating", elapsed_time, philo->philo_id);
		else if (status == SLEEPING && !dinner_finished(philo->table))
			printf("%ld %d is sleeping", elapsed_time, philo->philo_id);
		else if (status == THINKING && !dinner_finished(philo->table))
			printf("%ld %d is thinking", elapsed_time, philo->philo_id);
		else if (status == DIED && !dinner_finished(philo->table))
			printf("%ld %d died", elapsed_time, philo->philo_id);
		}
	pthread_mutex_unlock(&philo->table->print_mutex);
}
