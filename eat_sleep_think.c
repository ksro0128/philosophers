/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:40:19 by surkim            #+#    #+#             */
/*   Updated: 2023/08/31 11:53:34 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->tmp_lock));
	if (philo->info->die_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->tmp_lock));
		return ;
	}
	philo->eat_time = get_time();
	printf("%ld %d is eating\n", \
	philo->eat_time - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&(philo->info->tmp_lock));
	until_sleep(philo->eat_time + philo->info->time_to_eat, philo->info);
}

void	ft_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->tmp_lock));
	if (philo->info->die_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->tmp_lock));
		return ;
	}
	philo->sleep_time = get_time();
	printf("%ld %d is sleeping\n", \
	philo->sleep_time - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&(philo->info->tmp_lock));
	until_sleep(philo->sleep_time + philo->info->time_to_sleep, philo->info);
}

void	ft_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->tmp_lock));
	if (philo->info->die_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->tmp_lock));
		return ;
	}
	printf("%ld %d is thinking\n", \
	get_time() - philo->info->start_time, philo->id);
	pthread_mutex_unlock(&(philo->info->tmp_lock));
}
