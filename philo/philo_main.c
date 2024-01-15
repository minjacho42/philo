/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:38:13 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/15 22:09:29 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_thread_info(t_info *info)
{
	int idx;

	info->forks = malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->forks)
		return (1);
	idx = 0;
	while (idx < info->num_of_philo)
	{
		pthread_mutex_init(&info->forks[idx], NULL);
		idx++;
	}
	info->printer = malloc(sizeof(pthread_mutex_t));
	if (!info->printer)
	{
		free_mutex(info->forks, info->num_of_philo);
		return (1);
	}
	info->philo_thread = malloc(sizeof(pthread_t) * info->num_of_philo);
	if (!info->philo_thread)
	{
		free_mutex(info->forks, info->num_of_philo);
		free_mutex(info->printer, 1);
		return (1);
	}
	return (0);
}

static void	init_philo_arg(t_info *info, t_philo_arg *arg, int idx)
{
	arg->seat_idx = idx + 1;
	arg->l_fork = &info->forks[idx];
	arg->r_fork = &info->forks[(idx + 1) % info->num_of_philo];
	arg->printer = info->printer;
	arg->num_of_philo = info->num_of_philo;
	arg->time_to_eat = info->time_to_eat;
	arg->time_to_sleep = info->time_to_sleep;
	arg->eat_cnt = 0;
	arg->last_eat_time = 0;
}

static int	init_philo_args(t_info *info)
{
	int idx;

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

static int	init_info(int argc, char **argv, t_info *info)
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

int main(int argc, char *argv[])
{
	t_info	info;
	int		idx;
	int		eat_done;
	long long	cur_time;
	int		died;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_info(argc, argv, &info) == 1)
		return (1);
	idx = 0;
	info.died = 0;
	cur_time = get_time_mili_sc();
	while (idx < info.num_of_philo)
	{
		info.philo_args[idx].start_time = cur_time;
		info.philo_args[idx].last_eat_time = cur_time;
		info.philo_args[idx].died = &info.died;
		pthread_create(&info.philo_thread[idx], NULL, philo_routine, &info.philo_args[idx]);
		idx++;
	}
	while (1)
	{
		idx = 0;
		eat_done = 0;
		while (idx < info.num_of_philo)
		{
			cur_time = get_time_mili_sc();
			if (cur_time - info.philo_args[idx].last_eat_time > info.time_to_die)
			{
				info.died = 1;
				printf("%lld %d %s\n", get_time_mili_sc() - info.philo_args[idx].start_time, \
							idx + 1, "died");
				break;
			}
			if (info.must_eat > 0 && info.philo_args[idx].eat_cnt >= info.must_eat)
				eat_done++;
			idx++;
		}
		if (eat_done == info.num_of_philo || info.died)
			break;
		usleep(100);
	}
	while (idx < info.num_of_philo)
	{
		pthread_detach(info.philo_thread[idx]);
		idx++;
	}
}
