/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:00:47 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 00:44:50 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo_arg *arg, long long time, char *msg_str, \
						int die_print)
{
	pthread_mutex_lock(arg->printer);
	if (!get_die(arg) || die_print)
		printf("%lld %d %s\n", time - arg->start_time, arg->seat_idx, msg_str);
	pthread_mutex_unlock(arg->printer);
}

static int	first_think(t_philo_arg *arg)
{
	if (arg->seat_idx % 2 == 0)
		usleep(100);
	return (0);
}

static int	philo_think(t_philo_arg *arg)
{
	philo_print(arg, get_time_mili_sc(), "is thinking", 0);
	if (arg->eat_cnt == 0)
		first_think(arg);
	pthread_mutex_lock(arg->l_fork);
	philo_print(arg, get_time_mili_sc(), "has taken a fork", 0);
	pthread_mutex_lock(arg->r_fork);
	philo_print(arg, get_time_mili_sc(), "has taken a fork", 0);
	return (0);
}

void	*philo_routine(void *philo_arg)
{
	t_philo_arg	*arg;

	arg = (t_philo_arg *)philo_arg;
	arg->eat_cnt = 0;
	while (!get_die(arg))
	{
		philo_think(arg);
		if (get_die(arg))
		{
			pthread_mutex_unlock(arg->l_fork);
			pthread_mutex_unlock(arg->r_fork);
			break ;
		}
		philo_print(arg, get_time_mili_sc(), "is eating", 0);
		set_last_eat(arg);
		spend_time(arg->time_to_eat);
		pthread_mutex_unlock(arg->l_fork);
		pthread_mutex_unlock(arg->r_fork);
		arg->eat_cnt++;
		if (get_die(arg))
			break ;
		philo_print(arg, get_time_mili_sc(), "is sleeping", 0);
		spend_time(arg->time_to_sleep);
	}
	return (NULL);
}

void	run_philo(t_info *info)
{
	int			idx;
	long long	cur_time;

	idx = 0;
	cur_time = get_time_mili_sc();
	info->start_time = cur_time;
	while (idx < info->num_of_philo)
	{
		info->philo_args[idx].start_time = cur_time;
		info->philo_args[idx].last_eat_time = cur_time;
		info->philo_args[idx].died = 0;
		idx++;
	}
	idx = 0;
	while (idx < info->num_of_philo)
	{
		pthread_create(&info->philo_thread[idx], NULL, \
						philo_routine, &info->philo_args[idx]);
		idx++;
	}
}
