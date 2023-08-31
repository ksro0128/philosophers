/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:49:00 by surkim            #+#    #+#             */
/*   Updated: 2023/08/30 17:40:46 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_set(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->start_lock));
	pthread_mutex_lock(&(philo->info->tmp_lock));
	philo->eat_time = philo->info->start_time;
	pthread_mutex_unlock(&(philo->info->tmp_lock));
	pthread_mutex_unlock(&(philo->info->start_lock));
}

void	eating_sleeping_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->lock[philo->first_fork]));
	print_get_fork(philo);
	pthread_mutex_lock(&(philo->info->lock[philo->second_fork]));
	print_get_fork(philo);
	ft_eating(philo);
	pthread_mutex_unlock(&(philo->info->lock[philo->first_fork]));
	pthread_mutex_unlock(&(philo->info->lock[philo->second_fork]));
	ft_sleeping(philo);
	ft_thinking(philo);
}

void	*philo_cycle(void *tmp)
{
	t_philo	*philo;
	long	eat_cnt;

	philo = (t_philo *)tmp;
	wait_set(philo);
	if (philo->info->number_of_must_eat > 0)
		eat_cnt = 0;
	else
		eat_cnt = -2147483649;
	while (check_die(philo->info) == 0 && \
	eat_cnt < philo->info->number_of_must_eat)
	{
		eating_sleeping_thinking(philo);
		eat_cnt++;
	}
	if (eat_cnt == philo->info->number_of_must_eat)
	{
		pthread_mutex_lock(&(philo->info->tmp_lock));
		philo->eat_done = 1;
		pthread_mutex_unlock(&(philo->info->tmp_lock));
	}
	return (NULL);
}
