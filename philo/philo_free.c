/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:38:00 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/16 17:36:48 by minjacho         ###   ########.fr       */
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
		info->philo_args[idx].died = 1;
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
	int	idx;

	idx = 0;
	while (idx < info->num_of_philo)
	{
		pthread_mutex_destroy(&info->forks[idx]);
		idx++;
	}
	pthread_mutex_destroy(info->printer);
	free(info->philo_thread);
	free(info->forks);
	free(info->philo_args);
	free(info->printer);
}
