/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:33:54 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 00:28:36 by minjacho         ###   ########.fr       */
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

void	spend_time(long long time_to_spend)
{
	long long	start_time;

	start_time = get_time_mili_sc();
	while (time_to_spend + start_time > get_time_mili_sc())
		usleep(100);
}
