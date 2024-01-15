/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:00:47 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/15 22:17:19 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo_arg *arg, long long time, char *msg_str)
{
	pthread_mutex_lock(arg->printer);

	if (!*(arg->died))
		printf("%lld %d %s\n", time - arg->start_time, arg->seat_idx, msg_str);
	pthread_mutex_unlock(arg->printer);
}

void	*philo_routine(void *philo_arg)
{
	t_philo_arg	*arg;
	long long	start_time;
	long long	end_time;

	arg = (t_philo_arg *)philo_arg;
	while (1)
	{
		start_time = get_time_mili_sc();
		philo_print(arg, start_time, "is thinking");
		if (arg->eat_cnt == 0)
		{
			if (arg->seat_idx % 2 == 0)
				usleep(arg->time_to_eat * 900);
			else if (arg->num_of_philo % 2 == 1 && arg->seat_idx == arg->num_of_philo)
				usleep(100);
		}
		pthread_mutex_lock(arg->l_fork);
		philo_print(arg, get_time_mili_sc(), "has taken a fork");
		pthread_mutex_lock(arg->r_fork);
		philo_print(arg, get_time_mili_sc(), "has taken a fork");
		arg->last_eat_time = get_time_mili_sc();
		philo_print(arg, arg->last_eat_time, "is eating");
		start_time = arg->last_eat_time;
		while (get_time_mili_sc() - start_time < arg->time_to_eat)
			usleep(100);
		pthread_mutex_unlock(arg->l_fork);
		pthread_mutex_unlock(arg->r_fork);
		arg->eat_cnt++;
		start_time = get_time_mili_sc();
		philo_print(arg, get_time_mili_sc(), "is sleeping");
		while (get_time_mili_sc() - start_time < arg->time_to_sleep)
			usleep(100);
	}
}
