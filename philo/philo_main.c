/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:22:41 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/19 13:14:11 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arg(int argc, char **argv, t_args *arg)
{
	arg->num_of_philo = philo_atoi(argv[1]);
	if (arg->num_of_philo < 0)
		return (1);
	arg->time_to_die = philo_atoll(argv[2]);
	if (arg->time_to_die <= 0)
		return (1);
	arg->time_to_eat = philo_atoll(argv[3]);
	if (arg->time_to_eat <= 0)
		return (1);
	arg->time_to_sleep = philo_atoll(argv[4]);
	if (arg->time_to_sleep <= 0)
		return (1);
	if (argc > 5)
	{
		arg->must_eat = philo_atoi(argv[5]);
		if (arg->must_eat <= 0)
			return (1);
	}
	else
		arg->must_eat = -1;
	arg->died = 0;
	return (0);
}

int	init_mutex_list(t_args *args, t_mutexs *mutexs)
{
	int	idx;

	idx = 0;
	while (idx < args->num_of_philo)
	{
		if (pthread_mutex_init(&mutexs->forks[idx], NULL) || \
				pthread_mutex_init(&mutexs->cnt_mutex[idx], NULL) || \
					pthread_mutex_init(&mutexs->last_eat_mutex[idx], NULL))
		{
			free_one_mutex(mutexs->forks, args->num_of_philo);
			free_one_mutex(mutexs->cnt_mutex, args->num_of_philo);
			free_one_mutex(mutexs->last_eat_mutex, args->num_of_philo);
			return (1);
		}
		idx++;
	}
	return (0);
}

int	create_mutex_list(t_args *args, t_mutexs *mutexs)
{
	mutexs->forks = malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!mutexs->forks)
		return (1);
	mutexs->cnt_mutex = malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!mutexs->cnt_mutex)
	{
		free(mutexs->forks);
		return (1);
	}
	mutexs->last_eat_mutex = \
		malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!mutexs->last_eat_mutex)
	{
		free(mutexs->cnt_mutex);
		free(mutexs->forks);
		return (1);
	}
	return (init_mutex_list(args, mutexs));
}

int	init_mutex(t_args *args, t_mutexs *mutexs)
{
	mutexs->printer = malloc(sizeof(pthread_mutex_t));
	if (!mutexs->printer)
		return (1);
	if (pthread_mutex_init(mutexs->printer, NULL))
	{
		free(mutexs->printer);
		return (1);
	}
	mutexs->checker = malloc(sizeof(pthread_mutex_t));
	if (!mutexs->checker)
		return (1);
	if (pthread_mutex_init(mutexs->checker, NULL))
	{
		free_one_mutex(mutexs->printer, 1);
		free(mutexs->checker);
		return (1);
	}
	if (create_mutex_list(args, mutexs))
	{
		free_one_mutex(mutexs->printer, 1);
		free_one_mutex(mutexs->checker, 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args			arg;
	t_mutexs		mutexs;
	pthread_t		*philo_thread;
	t_philo_info	*philo_infos;

	if (!(argc == 5 || argc == 6))
		return (print_err("Argument error occured"));
	if (init_arg(argc, argv, &arg))
		return (print_err("Argument error occured"));
	if (init_mutex(&arg, &mutexs))
		return (print_err("mutex create error occured"));
	philo_thread = malloc(sizeof(pthread_t) * arg.num_of_philo);
	if (!philo_thread)
		return (print_err("malloc error"));
	philo_infos = malloc(sizeof(t_philo_info) * arg.num_of_philo);
	if (!philo_infos)
	{
		free_mutexs(&mutexs, &arg);
		return (print_err("malloc error"));
	}
	run_philo_thread(&arg, &mutexs, philo_thread, philo_infos);
	free_resource(&arg, &mutexs, philo_thread, philo_infos);
}
