/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:28 by surkim            #+#    #+#             */
/*   Updated: 2023/08/30 17:42:14 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_die(t_info *info)
{
	pthread_mutex_lock(&(info->tmp_lock));
	if (info->die_flag == 1)
	{
		pthread_mutex_unlock(&(info->tmp_lock));
		return (1);
	}
	pthread_mutex_unlock(&(info->tmp_lock));
	return (0);
}

void	print_get_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->tmp_lock));
	if (philo->info->die_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->tmp_lock));
		return ;
	}
	printf("%ldms %d has taken a fork\n", get_time() - philo->info->start_time, \
	philo->id);
	pthread_mutex_unlock(&(philo->info->tmp_lock));
}

void	until_sleep(long time, t_info *info)
{
	long	ctime;

	ctime = get_time();
	while (ctime < time)
	{
		if (check_die(info) == 1)
			break ;
		usleep(200);
		ctime = get_time();
	}
}
