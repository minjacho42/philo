/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:55:08 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 21:10:41 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pick_fork(t_philo_info *philo_info)
{
	pthread_mutex_lock(&philo_info->mutexs->\
			forks[philo_info->seat_idx - 1]);
	print_state(philo_info, 4);
	if (philo_info->arg->num_of_philo == 1)
	{
		while (!check_died(philo_info->arg, philo_info->mutexs))
			usleep(100);
		return (1);
	}
	pthread_mutex_lock(&philo_info->mutexs->\
			forks[philo_info->seat_idx % philo_info->arg->num_of_philo]);
	print_state(philo_info, 4);
	return (0);
}

static int	philo_think_eat(t_philo_info *philo_info)
{
	if (pick_fork(philo_info))
		return (1);
	if (check_died(philo_info->arg, philo_info->mutexs))
	{
		pthread_mutex_unlock(&philo_info->mutexs->\
			forks[philo_info->seat_idx - 1]);
		pthread_mutex_unlock(&philo_info->mutexs->\
			forks[philo_info->seat_idx % philo_info->arg->num_of_philo]);
		return (1);
	}
	print_state(philo_info, 1);
	set_last_eat(philo_info, get_time_milisc());
	spend_time(philo_info->arg->time_to_eat);
	pthread_mutex_unlock(&philo_info->mutexs->\
			forks[philo_info->seat_idx - 1]);
	pthread_mutex_unlock(&philo_info->mutexs->\
			forks[philo_info->seat_idx % philo_info->arg->num_of_philo]);
	set_eat_cnt(philo_info);
	return (0);
}

void	*philo_routine(void *info)
{
	t_philo_info	*philo_info;

	philo_info = info;
	print_state(philo_info, 3);
	if (!(philo_info->seat_idx % 2))
		spend_time(philo_info->arg->time_to_eat);
	while (!check_died(philo_info->arg, philo_info->mutexs))
	{
		if (philo_think_eat(philo_info))
			return (NULL);
		if (check_died(philo_info->arg, philo_info->mutexs))
			return (NULL);
		print_state(philo_info, 2);
		if (check_died(philo_info->arg, philo_info->mutexs))
			return (NULL);
		spend_time(philo_info->arg->time_to_sleep);
		if (check_died(philo_info->arg, philo_info->mutexs))
			return (NULL);
		print_state(philo_info, 3);
	}
	return (NULL);
}

void	monitor_main(t_args *arg, t_mutexs *mutexs, t_philo_info *philo_infos)
{
	int	idx;
	int	done_eat_cnt;

	while (!check_died(arg, mutexs))
	{
		idx = -1;
		done_eat_cnt = 0;
		while (++idx < arg->num_of_philo)
		{
			if (check_last_eat(&philo_infos[idx]) + arg->time_to_die <= \
				get_time_milisc())
			{
				set_died(arg, mutexs);
				print_state(&philo_infos[idx], 5);
				break ;
			}
			if (arg->must_eat > 0 && \
				check_eat_cnt(&philo_infos[idx]) >= arg->must_eat)
				done_eat_cnt++;
		}
		if (done_eat_cnt >= arg->num_of_philo)
			break ;
		usleep(100);
	}
	set_died(arg, mutexs);
}

void	run_philo_thread(t_args *arg, t_mutexs *mutexs, pthread_t *threads, \
							t_philo_info *philo_infos)
{
	int	idx;

	idx = 0;
	while (idx < arg->num_of_philo)
	{
		philo_infos[idx].arg = arg;
		philo_infos[idx].mutexs = mutexs;
		philo_infos[idx].eat_cnt = 0;
		philo_infos[idx].seat_idx = idx + 1;
		idx++;
	}
	idx = 0;
	arg->start_time = get_time_milisc();
	while (idx < arg->num_of_philo)
	{
		philo_infos[idx].last_eat = arg->start_time;
		pthread_create(&threads[idx], NULL, philo_routine, &philo_infos[idx]);
		idx++;
	}
	monitor_main(arg, mutexs, philo_infos);
	idx = -1;
	while (++idx < arg->num_of_philo)
		pthread_join(threads[idx], NULL);
}
