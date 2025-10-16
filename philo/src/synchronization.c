/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:53:27 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 14:41:41 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* Waiting for all threads to be ready to synchronize their start */
void	ft_spinlock(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->philos_ready))
	;
}
