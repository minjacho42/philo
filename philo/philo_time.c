/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:33:54 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/16 09:46:13 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_mili_sc(void)
{
	struct timeval	tp;
	long long		time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

int	spend_time(t_philo_arg *arg, long long start_time, long long time_to_spend)
{
	while (!*(arg->died) && get_time_mili_sc() - start_time < time_to_spend)
	{
		if (get_time_mili_sc() - arg->last_eat_time > arg->time_to_die)
		{
			*(arg->died) = 1;
			philo_print(arg, get_time_mili_sc(), "died!!", 1);
			return (1);
		}
		usleep(100);
	}
	if (*(arg->died))
		return (1);
	return (0);
}
