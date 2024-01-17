/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:33 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 10:51:50 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_eat(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->last_eat_mutex);
	arg->last_eat_time = get_time_mili_sc();
	pthread_mutex_unlock(arg->last_eat_mutex);
}

long long	get_last_eat(t_philo_arg *arg)
{
	long long	time;

	pthread_mutex_lock(arg->last_eat_mutex);
	time = arg->last_eat_time;
	pthread_mutex_unlock(arg->last_eat_mutex);
	return (time);
}

void	set_eat_cnt(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->eat_cnt_mutex);
	arg->eat_cnt++;
	pthread_mutex_unlock(arg->eat_cnt_mutex);
}

int	get_eat_cnt(t_philo_arg *arg)
{
	int	cnt;

	pthread_mutex_lock(arg->eat_cnt_mutex);
	cnt = arg->eat_cnt;
	pthread_mutex_unlock(arg->eat_cnt_mutex);
	return (cnt);
}
