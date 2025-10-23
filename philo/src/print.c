/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 19:53:25 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/23 14:27:44 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philo_status status, t_philo *philo)
{
	long	elapsed_time;

	elapsed_time = gettime(MILLISECOND) - philo->table->simulation_start;

	safe_mutex_handle(&philo->table->print_mutex, LOCK);
	if (philo->is_full)
	{
		safe_mutex_handle(&philo->table->print_mutex, UNLOCK);
		return ;
	}
	if ((status == TAKE_1_FORK || status == TAKE_2_FORK)
		&& !dinner_finished(philo->table))
		printf("%ld %d has taken a fork\n", elapsed_time, philo->philo_id);
	else if (status == EATING && !dinner_finished(philo->table))
		printf("%ld %d is eating\n", elapsed_time, philo->philo_id);
	else if (status == SLEEPING && !dinner_finished(philo->table))
		printf("%ld %d is sleeping\n", elapsed_time, philo->philo_id);
	else if (status == THINKING && !dinner_finished(philo->table))
		printf("%ld %d is thinking\n", elapsed_time, philo->philo_id);
	else if (status == DIED)
		printf("%ld %d died\n", elapsed_time, philo->philo_id);
	safe_mutex_handle(&philo->table->print_mutex, UNLOCK);
}
