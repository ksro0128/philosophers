/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:57 by surkim            #+#    #+#             */
/*   Updated: 2023/08/31 11:57:14 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	moniter(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_mutex_lock(&(info->tmp_lock));
		if (info->philo->eat_done == 0 && \
		info->philo[i].eat_time + info->time_to_die < get_time())
		{
			info->die_flag = 1;
			printf("%ld %d died\n", get_time() - info->start_time, i + 1);
			pthread_mutex_unlock(&(info->tmp_lock));
			return (1);
		}
		pthread_mutex_unlock(&(info->tmp_lock));
		i++;
	}
	return (0);
}

void	ft_moniter(t_info	*info)
{
	int	i;
	int	eat_done;

	until_sleep(info->start_time + info->time_to_die, info);
	while (moniter(info) == 0)
	{
		i = 0;
		eat_done = 0;
		while (i < info->number_of_philo)
		{
			pthread_mutex_lock(&(info->tmp_lock));
			eat_done += info->philo[i].eat_done;
			pthread_mutex_unlock(&(info->tmp_lock));
			i++;
		}
		if (eat_done == info->number_of_philo)
			break ;
		usleep(10);
	}
}

int	philo_thread_create(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_create(&(info->philo_thread[i]), NULL, \
		philo_cycle, &(info->philo[i])) != 0)
		{
			pthread_mutex_lock(&(info->tmp_lock));
			info->die_flag = 1;
			info->number_of_philo = i;
			pthread_mutex_unlock(&(info->tmp_lock));
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_thread_join(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_join(info->philo_thread[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	pthread_start(t_info *info)
{
	pthread_mutex_lock(&(info->start_lock));
	if (philo_thread_create(info) != 0)
	{
		philo_thread_join(info);
		pthread_mutex_unlock(&(info->start_lock));
		return (1);
	}
	info->start_time = get_time();
	pthread_mutex_unlock(&(info->start_lock));
	ft_moniter(info);
	if (philo_thread_join(info) != 0)
		return (1);
	return (0);
}
