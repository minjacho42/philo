/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:29:15 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 10:52:45 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'\
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	set_die(t_philo_arg *arg)
{
	pthread_mutex_lock(arg->die_mutex);
	arg->died = 1;
	pthread_mutex_unlock(arg->die_mutex);
}

int	get_die(t_philo_arg *arg)
{
	int	die;

	pthread_mutex_lock(arg->die_mutex);
	die = arg->died;
	pthread_mutex_unlock(arg->die_mutex);
	return (die);
}
