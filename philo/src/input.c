/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:35 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/09/13 17:19:51 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*Function assigning forks to a given philosopher.*/
static void fork_assign(t_philo *philo, t_fork *forks, int pos)
{
	//n-th philo will have n-th and (n+1)-th fork available
	if (philo->philo_id % 2 == 0) //avoid deadlock
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo->table->philo_num];
	}
	else
	{
		philo->first_fork = &forks[(pos + 1) % philo->table->philo_num];
		philo->second_fork = &forks[pos];
	}
	
}

static void philo_init(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (i < table->philo_num)
	{
		philo = table->philos + 1; //pointer to (i+1)-th philo
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->meal_count = 0;
		philo->table = table;
	}
	fork_assign(philo, table->forks, i);
}

static void data_init(t_table *table)
{
	int	i;

	table->is_end_of_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!(table->philos))
		error_exit("malloc error - philos");
	table->forks = malloc(sizeof(t_fork) * table->philo_num);
	if (!(table->forks))
		error_exit("malloc error - forks");
	i = -1;
	while (++i < table->philo_num) //init for mutexes
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].fork_id = i;
	}

}

static void parsing(t_table *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * 1e3;
	table->time_to_eat = ft_atoi(argv[3]) * 1e3;
	table->time_to_sleep = ft_atoi(argv[4]) * 1e3;
	if (table->time_to_die <= 0 || table->time_to_eat <=0 ||
		table->time_to_sleep <= 0)
	{
		error_exit("Timestamps must be positive numbers!");
	}
	if (argv[5])
		table->meal_limit = argv[5];
	else
		table->meal_limit = -1; //flag
}

void input_check_and_init(t_table *table, char **argv)
{
	parsing(table, argv);
	data_init(table);
}