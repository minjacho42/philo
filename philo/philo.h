/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:37:16 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/14 13:34:36 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo_arg
{
	int				seat_idx;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*printer;
	int				die;
	int				num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_eat_time;
	long long		start_time;
	int				eat_cnt;
}	t_philo_arg;

typedef struct s_info
{
	pthread_t		*philo_thread;
	t_philo_arg		*philo_args;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*printer;
	int				num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				must_eat;
}	t_info;

int			philo_atoi(const char *str);
int			philo_atoll(const char *str);
void		*philo_routine(void *philo_arg);
void		free_mutex(pthread_mutex_t *mutex, int size);
long long	get_time_mili_sc(void);
void	philo_print(pthread_mutex_t *printer, int num, char *msg_str, long long start_time);
#endif
