/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjamrosz <kjamrosz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 14:46:06 by kjamrosz          #+#    #+#             */
/*   Updated: 2025/10/16 14:31:28 by kjamrosz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*Print error message and exit(EXIT_FAILURE)*/
void error_exit(char *msg)
{
	printf("ERROR: %s\n", msg);
	exit(EXIT_FAILURE);
}

/* Returns time */
long	gettime(t_timecode timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("gettimeofday() error");
	if (timecode == SECOND)
		return (tv.tv_sec + (tv.tv_usec) / 1e6);
	else if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec) / 1e3);
	else if (timecode == MICROSECOND)
	{
		// printf("MICROSECOND\n");
		// printf("tv.tv_sec         = %ld\n", tv.tv_sec);
		// printf("(tv.tv_sec * 1e6) = %f\n", (tv.tv_sec * 1e6));
		// printf("tv.tv_usec        = %ld\n", tv.tv_usec);
		// printf("return            = %f\n", ((tv.tv_sec * 1e6) + tv.tv_usec));

		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	}
	else
		error_exit("gettime input error");
	return (42); 
}

void precise_usleep(long usec, t_table *table) //INCORRECT
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	// printf("start = %ld\n", start);
	while (gettime(MICROSECOND) - start < usec) // cannot finish itself !
	{
		// printf("\twhile in precise_usleep\n"); //del

		if (dinner_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		// printf("elapsed = %ld\trem = %ld\tstart = %ld\n", elapsed, rem, start); //del

		if (rem > 1e3)
			usleep(rem / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				;
	}
}

// void	ft_usleep(long usec)
// {
// 	long	start;

// 	start = get_time();
// 	while ((get_time() - start) < usec)
// 		usleep(500);
// }