/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:38:00 by minjacho          #+#    #+#             */
/*   Updated: 2024/01/12 12:40:03 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mutex, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		pthread_mutex_destroy(&mutex[idx]);
		idx++;
	}
	free(mutex);
}
