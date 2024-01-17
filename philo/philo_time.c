/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:58:00 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 20:59:56 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_milisc(void)
{
	struct timeval	tp;
	long long		time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}

long long	diff_tv(struct timeval *tv1, struct timeval *tv2)
{
	long long	sec_diff;
	long long	usec_diff;

	sec_diff = tv1->tv_sec - tv2->tv_sec;
	usec_diff = tv1->tv_usec - tv2->tv_usec;
	return (sec_diff * 1000000 + usec_diff);
}

void	spend_time(long long time)
{
	struct timeval	start_tv;
	struct timeval	cur_tv;

	gettimeofday(&start_tv, NULL);
	gettimeofday(&cur_tv, NULL);
	while (time * 1000 >= diff_tv(&cur_tv, &start_tv))
	{
		usleep(100);
		gettimeofday(&cur_tv, NULL);
	}
}

void	print_state(t_philo_info *philo_info, int state)
{
	char		*str;
	long long	time;

	time = get_time_milisc();
	pthread_mutex_lock(philo_info->mutexs->printer);
	if (state == 5)
	{
		printf("%lld %d %s\n", time - philo_info->arg->start_time, \
					philo_info->seat_idx, "died");
		state = 0;
	}
	if (check_died(philo_info->arg, philo_info->mutexs))
		state = 0;
	if (state == 1)
		str = "is eating";
	else if (state == 2)
		str = "is sleeping";
	else if (state == 3)
		str = "is thinking";
	else if (state == 4)
		str = "has taken a fork";
	if (state)
		printf("%lld %d %s\n", time - philo_info->arg->start_time, \
					philo_info->seat_idx, str);
	pthread_mutex_unlock(philo_info->mutexs->printer);
}
