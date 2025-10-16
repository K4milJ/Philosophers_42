/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:50:41 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 13:53:43 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	//printf("argc = %d\n", argc);
	t_table	table;

	// printf(GREEN "HELLO1\n" RESET);
	if (argc == 5 || argc == 6)
	{
		// printf(GREEN "HELLO2\n" RESET);	//del
		//table = malloc(sizeof(t_table *));
		input_check_and_init(&table, argv); //here all fine
		
		// parsing(&table, argv);
		// data_init(&table);

		start_the_dinner(&table); //here's an issue
		//clean_exit(table); //TODO - no leaks
	}
	else
	{
		error_exit("Incorrect input!");
	}
	
	return (0);
}