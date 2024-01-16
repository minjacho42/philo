/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:00:47 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/16 09:48:10 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo_arg *arg, long long time, char *msg_str, int die_print)
{
	pthread_mutex_lock(arg->printer);
	if (!*(arg->died) || die_print)
		printf("%lld %d %s\n", time - arg->start_time, arg->seat_idx, msg_str);
	if (!die_print)
		pthread_mutex_unlock(arg->printer);
}

void	*philo_routine(void *philo_arg)
{
	t_philo_arg	*arg;
	long long	start_time;
	long long	end_time;
	int			died;

	arg = (t_philo_arg *)philo_arg;
	while (1)
	{
		start_time = get_time_mili_sc();
		if (get_time_mili_sc() - arg->last_eat_time > arg->time_to_die)
		{
			*(arg->died) = 1;
			philo_print(arg, get_time_mili_sc(), "died!!", 1);
			return (NULL);
		}
		philo_print(arg, start_time, "is thinking", 0);
		if (arg->eat_cnt == 0)
		{
			if (arg->seat_idx % 2 == 0)
			{
				if (spend_time(arg, start_time, arg->time_to_eat * 9 / 10))
					return (NULL);
			}
			else if (arg->num_of_philo % 2 == 1 && arg->seat_idx == arg->num_of_philo)
				usleep(100);
		}
		if (*(arg->died))
			return (NULL);
		if (get_time_mili_sc() - arg->last_eat_time > arg->time_to_die)
		{
			*(arg->died) = 1;
			philo_print(arg, get_time_mili_sc(), "died!!", 1);
			return (NULL);
		}
		pthread_mutex_lock(arg->l_fork);
		philo_print(arg, get_time_mili_sc(), "has taken a fork", 0);
		pthread_mutex_lock(arg->r_fork);
		if (get_time_mili_sc() - arg->last_eat_time > arg->time_to_die)
		{
			*(arg->died) = 1;
			philo_print(arg, get_time_mili_sc(), "died!!", 1);
			return (NULL);
		}
		philo_print(arg, get_time_mili_sc(), "has taken a fork", 0);
		if (*(arg->died))
			return (NULL);
		if (get_time_mili_sc() - arg->last_eat_time > arg->time_to_die)
		{
			*(arg->died) = 1;
			philo_print(arg, get_time_mili_sc(), "died!!", 1);
			return (NULL);
		}
		arg->last_eat_time = get_time_mili_sc();
		philo_print(arg, arg->last_eat_time, "is eating", 0);
		if (spend_time(arg, arg->last_eat_time, arg->time_to_eat))
			return (NULL);
		pthread_mutex_unlock(arg->l_fork);
		pthread_mutex_unlock(arg->r_fork);
		arg->eat_cnt++;
		start_time = get_time_mili_sc();
		philo_print(arg, get_time_mili_sc(), "is sleeping", 0);
		if (spend_time(arg, start_time, arg->time_to_sleep))
			return (NULL);
	}
}
