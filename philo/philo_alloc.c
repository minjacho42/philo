/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:38:00 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 10:54:10 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mutex, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		pthread_mutex_destroy(&mutex[idx]);
		idx++;
	}
	free(mutex);
}

void	kill_philo(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		set_die(&info->philo_args[idx]);
		idx++;
	}
	idx = 0;
	while (idx < info->num_of_philo)
	{
		pthread_join(info->philo_thread[idx], NULL);
		idx++;
	}
}

void	free_resource(t_info *info)
{
	free_mutex(info->forks, info->num_of_philo);
	free_mutex(info->die_mutex, info->num_of_philo);
	free_mutex(info->last_eat_mutex, info->num_of_philo);
	pthread_mutex_destroy(info->printer);
	free(info->philo_thread);
	free(info->philo_args);
	free(info->printer);
}

static void	init_philo_arg(t_info *info, t_philo_arg *arg, int idx)
{
	arg->seat_idx = idx + 1;
	arg->l_fork = &info->forks[idx];
	arg->r_fork = &info->forks[(idx + 1) % info->num_of_philo];
	arg->die_mutex = &info->die_mutex[idx];
	arg->last_eat_mutex = &info->last_eat_mutex[idx];
	arg->eat_cnt_mutex = &info->eat_cnt_mutex[idx];
	arg->printer = info->printer;
	arg->num_of_philo = info->num_of_philo;
	arg->time_to_eat = info->time_to_eat;
	arg->time_to_sleep = info->time_to_sleep;
	arg->time_to_die = info->time_to_die;
	arg->eat_cnt = 0;
	arg->last_eat_time = 0;
}

int	init_philo_args(t_info *info)
{
	int	idx;

	idx = 0;
	info->philo_args = malloc(sizeof(t_philo_arg) * info->num_of_philo);
	if (!info->philo_args)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->printer, 1);
		free(info->philo_thread);
		return (1);
	}
	while (idx < info->num_of_philo)
	{
		init_philo_arg(info, &info->philo_args[idx], idx);
		idx++;
	}
	return (0);
}
