/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:41 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 17:39:35 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		input_check_and_init(&table, argv); //here all fine

		start_the_dinner(&table); //here's an issue
		clean_exit(&table);
	}
	else
	{
		error_exit("Incorrect input!");
	}
	
	return (0);
}