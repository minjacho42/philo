/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:31:46 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 10:51:05 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_mutex_array(t_info *info)
{
	int	idx;

	info->last_eat_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->last_eat_mutex)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->die_mutex, info->num_of_philo);
		return (1);
	}
	idx = -1;
	while (++idx < info->num_of_philo)
		pthread_mutex_init(&info->last_eat_mutex[idx], NULL);
	info->eat_cnt_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->eat_cnt_mutex)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->die_mutex, info->num_of_philo);
		free_mutex(info->last_eat_mutex, info->num_of_philo);
		return (1);
	}
	idx = -1;
	while (++idx < info->num_of_philo)
		pthread_mutex_init(&info->eat_cnt_mutex[idx], NULL);
	return (0);
}

static int	init_thread_info_sub(t_info *info)
{
	if (create_mutex_array(info))
		return (1);
	info->printer = malloc(sizeof(pthread_mutex_t));
	if (!info->printer)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->die_mutex, info->num_of_philo);
		free_mutex(info->last_eat_mutex, info->num_of_philo);
		free_mutex(info->eat_cnt_mutex, info->num_of_philo);
		return (1);
	}
	info->philo_thread = malloc(sizeof(pthread_t) * info->num_of_philo);
	if (!info->philo_thread)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->die_mutex, info->num_of_philo);
		free_mutex(info->last_eat_mutex, info->num_of_philo);
		free_mutex(info->eat_cnt_mutex, info->num_of_philo);
		free_mutex(info->printer, 1);
		return (1);
	}
	return (0);
}

static int	init_thread_info(t_info *info)
{
	int	idx;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks)
		return (1);
	idx = -1;
	while (++idx < info->num_of_philo)
		pthread_mutex_init(&info->forks[idx], NULL);
	info->die_mutex = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->die_mutex)
	{
		free_mutex(info->forks, info->num_of_philo);
		return (1);
	}
	idx = -1;
	while (++idx < info->num_of_philo)
		pthread_mutex_init(&info->die_mutex[idx], NULL);
	if (init_thread_info_sub(info))
		return (1);
	return (0);
}

int	init_info(int argc, char **argv, t_info *info)
{
	info->num_of_philo = philo_atoi(argv[1]);
	if (info->num_of_philo < 0)
		return (1);
	info->time_to_die = philo_atoll(argv[2]);
	if (info->time_to_die <= 0)
		return (1);
	info->time_to_eat = philo_atoll(argv[3]);
	if (info->time_to_eat <= 0)
		return (1);
	info->time_to_sleep = philo_atoll(argv[4]);
	if (info->time_to_sleep <= 0)
		return (1);
	if (argc > 5)
	{
		info->must_eat = philo_atoi(argv[5]);
		if (info->must_eat <= 0)
			return (1);
	}
	else
		info->must_eat = -1;
	if (init_thread_info(info) == 1)
		return (1);
	if (init_philo_args(info) == 1)
		return (1);
	return (0);
}
