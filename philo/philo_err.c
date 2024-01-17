/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:34:20 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 19:07:08 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_err(char *err_str)
{
	write(2, "philo :", 8);
	write(2, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
	return (1);
}

void	free_one_mutex(pthread_mutex_t *mutexs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutexs[i]);
		i++;
	}
	free(mutexs);
}

void	free_mutexs(t_mutexs *mutexs, t_args *arg)
{
	free_one_mutex(mutexs->forks, arg->num_of_philo);
	free_one_mutex(mutexs->cnt_mutex, arg->num_of_philo);
	free_one_mutex(mutexs->checker, 1);
	free_one_mutex(mutexs->printer, 1);
}

void	free_resource(t_args *arg, t_mutexs *mutexs, pthread_t *threads, \
							t_philo_info *philo_infos)
{
	free_mutexs(mutexs, arg);
	free(threads);
	free(philo_infos);
}