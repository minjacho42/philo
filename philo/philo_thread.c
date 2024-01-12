/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:00:47 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/12 13:20:55 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_print(pthread_mutex_t *printer, int num, char *msg_str)
{
	pthread_mutex_lock(printer);
	printf("%lld %d %s\n", 0LL, num, msg_str);
	pthread_mutex_unlock(printer);
}

static int	philo_eat(t_philo_arg *arg)
{

	if (arg->seat_idx % 2 == 0)
	{
		pthread_mutex_lock(arg->l_fork);
		pthread_mutex_lock(arg->r_fork);
	}
	else
	{
		pthread_mutex_lock(arg->r_fork);
		pthread_mutex_lock(arg->l_fork);
	}

}

void	*philo_routine(void *philo_arg)
{
	t_philo_arg	*arg;

	arg = (t_philo_arg *)philo_arg;
	if (arg->seat_idx % 2 == 0)
	{

	}
}
