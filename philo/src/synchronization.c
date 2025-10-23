/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:27 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/23 14:44:53 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* Waiting for all threads to be ready to synchronize their start */
void	ft_spinlock(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->philos_ready))
		;
}

bool	all_philos_running(pthread_mutex_t *mutex, long *running_philos_num,
			long philo_num)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*running_philos_num == philo_num)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	desync_philos(t_philo *philo)
{
	if (philo->table->philo_num % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->philo_id % 2)
			thinking(philo, true);
	}
}
