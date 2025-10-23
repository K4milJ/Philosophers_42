/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:50:00 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/23 14:46:31 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_long(pthread_mutex_t *mutex, long *dest, long src)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = src;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *val)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool src)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = src;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *val)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *val;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

bool	dinner_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->is_end_of_simulation));
}
