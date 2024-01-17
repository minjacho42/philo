/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:38:13 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 10:48:40 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	monitor_main(t_info *info)
{
	int			idx;
	int			complete_eat;
	long long	check_time;

	while (1)
	{
		idx = 0;
		complete_eat = 0;
		check_time = get_time_mili_sc();
		while (!info->died && idx < info->num_of_philo)
		{
			if (check_time - get_last_eat(&info->philo_args[idx]) > \
					info->time_to_die)
				info->died = 1;
			if (info->must_eat > 0 && get_eat_cnt(&info->philo_args[idx]) >= \
					info->must_eat)
				complete_eat++;
			idx++;
		}
		if (info->died || complete_eat >= info->num_of_philo)
			break ;
		usleep(100);
	}
	info->died_philo = idx;
	return (check_time);
}

int	main(int argc, char *argv[])
{
	t_info		info;
	long long	check_time;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_info(argc, argv, &info) == 1)
		return (1);
	run_philo(&info);
	info.died = 0;
	check_time = monitor_main(&info);
	kill_philo(&info);
	if (info.died)
	{
		pthread_mutex_lock(info.printer);
		printf("%lld %d died\n", check_time - info.start_time, info.died_philo);
		pthread_mutex_unlock(info.printer);
	}
	free_resource(&info);
}
