/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:50:00 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/04 18:40:20 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* Function to safely get or set bool, dest is is a pointer to value we want to set or get */
bool	manage_bool(pthread_mutex_t *mutex, bool *dest, bool val, t_action action)
{
	bool	res;

	res = false;
	if (action == SET)
	{
		pthread_mutex_lock(mutex);
		*dest = val;
		pthread_mutex_unlock(mutex);
		return (true); //unnedeed
	}
	else if (action == GET)
	{
		pthread_mutex_lock(mutex);
		res = *dest;
		pthread_mutex_unlock(mutex);
		return (true); //unnedeed
	}
	return (res); //it's probably not a good approach
}