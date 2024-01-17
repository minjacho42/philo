/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:07:22 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 20:56:52 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_died(t_args *arg, t_mutexs *mutexs)
{
	pthread_mutex_lock(mutexs->checker);
	arg->died = 1;
	pthread_mutex_unlock(mutexs->checker);
}

void	set_eat_cnt(t_philo_info *philo_info)
{
	int	eat_cnt;

	pthread_mutex_lock(&philo_info->mutexs->\
							cnt_mutex[philo_info->seat_idx - 1]);
	eat_cnt = philo_info->eat_cnt;
	philo_info->eat_cnt = eat_cnt + 1;
	pthread_mutex_unlock(&philo_info->mutexs->\
							cnt_mutex[philo_info->seat_idx - 1]);
}

void	set_last_eat(t_philo_info *philo_info, long long last_eat)
{
	pthread_mutex_lock(&philo_info->mutexs->\
							last_eat_mutex[philo_info->seat_idx - 1]);
	philo_info->last_eat = last_eat;
	pthread_mutex_unlock(&philo_info->mutexs->\
							last_eat_mutex[philo_info->seat_idx - 1]);
}
