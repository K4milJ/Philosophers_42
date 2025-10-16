/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:35 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 13:53:51 by kjamrosz         ###   ########.fr       */
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
	while (++i < table->philo_num)
	{
		philo = table->philos + i; //pointer to (i+1)-th philo
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->meal_count = 0;
		philo->table = table;
		// pthread_mutex_init(&philo->philo_mutex, NULL);
		safe_mutex_handle(&philo->philo_mutex, INIT);
	
		fork_assign(philo, table->forks, i);
	}
}

/* Initializes data */
void data_init(t_table *table)
{
	int	i;

	table->is_end_of_simulation = false;
	table->philos_ready = false;
	// pthread_mutex_init(&table->table_mutex, NULL);
	// pthread_mutex_init(&table->print_mutex, NULL);
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->print_mutex, INIT);
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_num);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_num);
	// table->philos = malloc(sizeof(t_philo) * table->philo_num);
	// if (!(table->philos))
	// 	error_exit("malloc error - philos");
	// table->forks = malloc(sizeof(t_fork) * table->philo_num);
	// if (!(table->forks))
	// 	error_exit("malloc error - forks");
	i = -1;
	while (++i < table->philo_num) //init for mutexes
	{
		// pthread_mutex_init(&table->forks[i].fork, NULL);
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	// printf(YELLOW "data init'ED\n" RESET); 	//del
}

/* Saves input data to the struct */
void parsing(t_table *table, char **argv)
{
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die <= 6e4 || table->time_to_eat <= 6e4 ||
		table->time_to_sleep <= 6e4)
	{
		error_exit("Timestamps must bigger than 60ms");
	}
	if (argv[5]) //what if last number is negative?
		table->meal_limit = ft_atol(argv[5]);
	else
		table->meal_limit = -1; //flag
	// printf(YELLOW "parsing END\n" RESET); 	//del
}

void input_check_and_init(t_table *table, char **argv)
{
	// printf(YELLOW "input_check_and_init\n" RESET); 	//del
	parsing(table, argv);
	data_init(table);
}