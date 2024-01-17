/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:23:00 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/17 20:57:55 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_args
{
	int			num_of_philo;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			must_eat;
	int			died;
	long long	start_time;
}	t_args;

typedef struct s_mutexs
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*cnt_mutex;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*printer;
	pthread_mutex_t	*checker;
}	t_mutexs;

typedef struct s_philo_info
{
	t_args		*arg;
	t_mutexs	*mutexs;
	int			seat_idx;
	long long	last_eat;
	int			eat_cnt;
}	t_philo_info;

/*===================philo_atoi.c===================*/
int			philo_atoi(const char *str);
long long	philo_atoll(const char *str);

/*===================philo_atoi_util.c===================*/
int			ft_isspace(char c);
int			ft_isdigit(char c);

/*===================philo_err.c===================*/
int			print_err(char *err_str);
void		free_one_mutex(pthread_mutex_t *mutexs, int size);
void		free_mutexs(t_mutexs *mutexs, t_args *arg);
void		free_resource(t_args *arg, t_mutexs *mutexs, pthread_t *threads, \
							t_philo_info *philo_infos);

/*===================philo_thread.c===================*/
void		run_philo_thread(t_args *arg, t_mutexs *mutexs, pthread_t *threads, \
							t_philo_info *philo_infos);

/*===================philo_time.c===================*/
long long	get_time_milisc(void);
void		spend_time(long long time);
void		print_state(t_philo_info *philo_info, int state);

/*===================philo_checker.c===================*/
int			check_died(t_args *arg, t_mutexs *mutexs);
int			check_eat_cnt(t_philo_info *philo_info);
long long	check_last_eat(t_philo_info *philo_info);

/*===================philo_setter.c===================*/
void		set_died(t_args *arg, t_mutexs *mutexs);
void		set_eat_cnt(t_philo_info *philo_info);
void		set_last_eat(t_philo_info *philo_info, long long last_eat);

#endif
