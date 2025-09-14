/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:11:13 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/09/14 12:21:17 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*Print error message and exit(EXIT_FAILURE)*/
void error_exit(char *msg)
{
	printf("ERROR: %s\n", msg);
	exit(EXIT_FAILURE);
}