/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 10:57:42 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/14 18:14:35 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	thinking(t_philo *philo) //to be developed
{
	print_status(THINKING, philo, DEBUG_MODE);
}

static void	eating(t_philo *philo)
{
	// printf(RED "EATING\n" RESET); 	//del
	
	//lock
	// pthread_mutex_lock(&philo->first_fork->fork);
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	print_status(TAKE_1_FORK, philo, DEBUG_MODE);
	// pthread_mutex_lock(&philo->second_fork->fork);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	print_status(TAKE_2_FORK, philo, DEBUG_MODE);

	//do the stuff
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meal_count++;
	print_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meal_limit > 0
		&& philo->meal_count == philo->table->meal_limit)
		set_bool(&philo->philo_mutex, &philo->is_full, true);
	
	//unlock
	// pthread_mutex_unlock(&philo->first_fork->fork);
	// pthread_mutex_unlock(&philo->second_fork->fork);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
}

static void	*simulation(void *input) //func manages only 1 philo
{	//SOME ISSUE HERE
	t_philo	*philo;

	philo = (t_philo *)input;
	
	// we have to wait for all the threads - spinlock
	ft_spinlock(philo->table); //THERE IS SEGFAULT
	// printf(MAGENTA "we've done ft_spinlock()\n" RESET); 	//del
	// return NULL; //DEL
	
	while (!dinner_finished(philo->table))
	{
		if (philo->is_full) //is it thread safe?
			break ;
		eating(philo);

		print_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->time_to_sleep, philo->table);

		thinking(philo);
	}
	return (NULL);
}

void	start_the_dinner(t_table *table)
{
	//printf(BLUE "start_the_dinner\n" RESET); 	//del

	int	i;

	i = -1;
	if (table->meal_limit == 0)
		return ;
	else if (table->philo_num == 1)
		; //todo
	else
		while (++i < table->philo_num) //in this while we have an issue
		{
			// printf(CYAN "create philo %d\n" RESET, i); 	//del

			// pthread_create(&table->philos[i].thread_id, NULL, simulation,
			// 	&table->philos[i]); //there is some error here
			safe_thread_handle(&table->philos[i].thread_id, simulation,
					&table->philos[i], CREATE);
		}
	//philos are ready

	//start
	table->simulation_start = gettime(MILLISECOND);
	// printf(GREEN "we got time\n" RESET); 	//del

	// pthread_mutex_lock(&table->table_mutex);
	// table->philos_ready = true;
	// pthread_mutex_unlock(&table->table_mutex);
	set_bool(&table->table_mutex, &table->philos_ready, true);

	// sleep(10);
	// return ; //DEL
	
	//we should check if there is some error with (UN)LOCK
	// printf(GREEN "======\n" RESET); 	//del

	i = -1;
	while (++i < table->philo_num)
	{
		// printf(BLUE "while philo %d\n" RESET, i); 	//del

		// pthread_join(table->philos[i].thread_id, NULL);
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		//check for errors when joining
	}

	// in this line, all philos are full

}