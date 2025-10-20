/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:57:42 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 17:39:18 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*one_philo(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	ft_spinlock(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	safe_mutex_handle(&philo->table->table_mutex, LOCK);
	philo->table->running_philos_num++;
	safe_mutex_handle(&philo->table->table_mutex, UNLOCK);
	print_status(TAKE_1_FORK, philo, DEBUG_MODE);
	while (!dinner_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	thinking(t_philo *philo, bool before_sim)
{
	long	t_think;
	long	t_eat;
	long	t_sleep;

	if (!before_sim)
		print_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->philo_num % 2 == 0)
		return;

	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	eating(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_1_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_2_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_count++;
	print_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meal_limit > 0
		&& philo->meal_count == philo->table->meal_limit)
		set_bool(&philo->philo_mutex, &philo->is_full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*simulation(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	ft_spinlock(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	safe_mutex_handle(&philo->table->table_mutex, LOCK);
	philo->table->running_philos_num++;
	safe_mutex_handle(&philo->table->table_mutex, UNLOCK);
	desync_philos(philo);
	while (!dinner_finished(philo->table))
	{
		if (philo->is_full)
			break ;
		eating(philo);
		print_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_the_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->meal_limit == 0)
		return ;
	else if (table->philo_num == 1)
		safe_thread_handle(&table->philos[0].thread_id, one_philo,
			&table->philos[0], CREATE);
	else
		while (++i < table->philo_num) //in this while we have an issue
		{
			safe_thread_handle(&table->philos[i].thread_id, simulation,
					&table->philos[i], CREATE);
		}
	safe_thread_handle(&table->monitor, dinner_monitor, table, CREATE);
	table->simulation_start = gettime(MILLISECOND);
	set_bool(&table->table_mutex, &table->philos_ready, true);
	i = -1;
	while (++i < table->philo_num)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->is_end_of_simulation, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}