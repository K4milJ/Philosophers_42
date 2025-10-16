/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:33:12 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 17:07:27 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_philo_dead(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	if (elapsed > (philo->table->time_to_die / 1e3))
		return (true);
	return (false);
}

void	*dinner_monitor(void *input)
{
	int		i;
	t_table	*table;

	table = (t_table *)input;
	while (!all_philos_running(&table->table_mutex, &table->running_philos_num,
			table->philo_num)) //spinlock
		;
	while (!dinner_finished(table))
	{
		i = -1;
		while (++i < table->philo_num && !dinner_finished(table))
		{
			if (is_philo_dead(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->is_end_of_simulation, true);
				print_status(DIED, table->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}