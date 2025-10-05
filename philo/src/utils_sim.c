/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:50:00 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/05 14:25:33 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// functions in this file are very inelegant, DON'T LOOK AT THEM :p
// TO BE FIXED!

/* Function to safely get or set long, dest is is a pointer to value we want to set or get */
long	manage_long(pthread_mutex_t *mutex, long *dest, long val, t_action action)
{
	long	res;

	res = 0;
	if (action == SET)
	{
		pthread_mutex_lock(mutex);
		*dest = val;
		pthread_mutex_unlock(mutex);
		return (-42); //unnedeed
	}
	else if (action == GET)
	{
		pthread_mutex_lock(mutex);
		res = *dest;
		pthread_mutex_unlock(mutex);
		return (res);
	}
	return (res); //it's probably not a good approach
}

/* Function to safely get or set bool, dest is is a pointer to value we want to set or get */
bool	manage_bool(pthread_mutex_t *mutex, bool *dest, bool val, t_action action)
{
	// printf(YELLOW "inside manage BOOL\n" RESET); 	//del

	bool	res;

	res = false;
	if (action == SET)
	{
		printf(YELLOW "SET BOOL\n" RESET); 	//del
		pthread_mutex_lock(mutex);
		*dest = val;
		pthread_mutex_unlock(mutex);
		return (true); //unnedeed
	}
	else if (action == GET)
	{
		printf(YELLOW "GET BOOL\n" RESET); 	//del

		pthread_mutex_lock(mutex);
		res = *dest;
		pthread_mutex_unlock(mutex);
		return (true); //unnedeed
	}
	return (res); //it's probably not a good approach
}

bool dinner_finished(t_table *table)
{
	return (manage_bool(&table->table_mutex, &table->is_end_of_simulation, NULL, GET));
}