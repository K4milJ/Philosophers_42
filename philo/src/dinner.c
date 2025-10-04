/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:57:42 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/04 17:54:47 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	simulation(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	
	// we have to wait for all the threads - spinlock
	ft_spinlock(philo->table);

	while (!dinner_finished()) //TODO
	{
		if (philo->is_full)
			break ;
		// eating();
		// sleeping();
		// thinking();
	}
}

void	start_the_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->meal_limit == 0)
		return ;
	else
		while (++i < table->philo_num)
		{
			pthread_create(&table->philos[i].thread_id, NULL, simulation,
				&table->philos[i]);
		}
	//philos are ready

	//start
	table->simulation_start = gettime();

	pthread_mutex_lock(&table->table_mutex);
	table->philos_ready = true;
	pthread_mutex_unlock(&table->table_mutex);
	//we should check if there is some error with (UN)LOCK

	i = -1;
	while (++i < table->philo_num)
	{
		pthread_join(&table->philos[i].thread_id, NULL);
		//check for errors when joining
	}

}