/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:37:16 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/16 17:38:57 by minjacho         ###   ########.fr       */
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
	int				num_of_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		last_eat_time;
	long long		start_time;
	int				eat_cnt;
	int				died;
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
	int				died;
	int				died_philo;
	long long		start_time;
}	t_info;

/*================philo_atoi.c================*/
int			philo_atoi(const char *str);
int			philo_atoll(const char *str);

/*================philo_util.c================*/
int			ft_isspace(char c);
int			ft_isdigit(char c);

/*================philo_init.c================*/
int			init_info(int argc, char **argv, t_info *info);

/*================philo_thread.c================*/
void		free_mutex(pthread_mutex_t *mutex, int size);
void		kill_philo(t_info *info);
void		free_resource(t_info *info);

/*================philo_thread.c================*/
void		run_philo(t_info *info);
void		*philo_routine(void *philo_arg);
void		philo_print(t_philo_arg *arg, long long time, \
							char *msg_str, int die_print);

/*================philo_time.c================*/
long long	get_time_mili_sc(void);
void		spend_time(t_philo_arg *arg, long long start_time, \
							long long time_to_spend);
#endif
