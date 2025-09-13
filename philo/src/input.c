/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:35 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/09/13 15:06:00 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void data_init(t_table *table)
{
	table->is_end_of_simulation = false;
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!(table->philos))
		error_exit("malloc error - philos");
	table->forks = malloc(sizeof(t_fork) * table->philo_num);
	if (!(table->forks))
		error_exit("malloc error - forks");
	//now we need to take care of mutex
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