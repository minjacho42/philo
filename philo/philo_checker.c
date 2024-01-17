/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:54:58 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 20:56:34 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(t_args *arg, t_mutexs *mutexs)
{
	int	died;

	pthread_mutex_lock(mutexs->checker);
	died = arg->died;
	pthread_mutex_unlock(mutexs->checker);
	return (died);
}

int	check_eat_cnt(t_philo_info *philo_info)
{
	int	eat_cnt;

	pthread_mutex_lock(&philo_info->mutexs->\
							cnt_mutex[philo_info->seat_idx - 1]);
	eat_cnt = philo_info->eat_cnt;
	pthread_mutex_unlock(&philo_info->mutexs->\
							cnt_mutex[philo_info->seat_idx - 1]);
	return (eat_cnt);
}

long long	check_last_eat(t_philo_info *philo_info)
{
	long long	last_eat;

	pthread_mutex_lock(&philo_info->mutexs->\
							last_eat_mutex[philo_info->seat_idx - 1]);
	last_eat = philo_info->last_eat;
	pthread_mutex_unlock(&philo_info->mutexs->\
							last_eat_mutex[philo_info->seat_idx - 1]);
	return (last_eat);
}
