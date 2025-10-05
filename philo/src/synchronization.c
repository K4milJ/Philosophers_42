/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:27 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/05 11:11:42 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* Waiting for all threads to be ready to synchronize their start */
void	ft_spinlock(t_table *table)
{
	while (!manage_bool(&table->table_mutex, &table->philos_ready, NULL, GET))
	; // I hope it will work with NULL as value, we'll see
}
