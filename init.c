/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:43 by surkim            #+#    #+#             */
/*   Updated: 2023/08/30 16:54:15 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_info(t_info *info, char *argv[])
{
	info->die_flag = 0;
	info->number_of_philo = ft_atol(argv[1]);
	if (info->number_of_philo <= 0 || info->number_of_philo > 2147483647)
		return (1);
	info->time_to_die = ft_atol(argv[2]);
	if (info->time_to_die <= 0 || info->time_to_die > 2147483647)
		return (1);
	info->time_to_eat = ft_atol(argv[3]);
	if (info->time_to_eat <= 0 || info->time_to_eat > 2147483647)
		return (1);
	info->time_to_sleep = ft_atol(argv[4]);
	if (info->time_to_sleep <= 0 || info->time_to_sleep > 2147483647)
		return (1);
	if (argv[5] != NULL)
		info->number_of_must_eat = ft_atol(argv[5]);
	else
		info->number_of_must_eat = -1;
	if (info->number_of_must_eat < -1 || info->number_of_must_eat > 2147483647)
		return (1);
	return (0);
}

int	make_info_2(t_info *info)
{
	info->lock = (pthread_mutex_t *)malloc(sizeof \
	(pthread_mutex_t) * info->number_of_philo);
	if (info->lock == NULL)
		return (1);
	info->philo_thread = (pthread_t *)malloc(sizeof \
	(pthread_t) * info->number_of_philo);
	if (info->philo_thread == NULL)
	{
		free(info->lock);
		return (1);
	}
	info->philo = (t_philo *)malloc(sizeof \
	(t_philo) * info->number_of_philo);
	if (info->philo == NULL)
	{
		free(info->lock);
		free(info->philo_thread);
		return (1);
	}
	return (0);
}

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (pthread_mutex_init(&(info->lock[i]), NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(info->tmp_lock), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(info->start_lock), NULL) != 0)
		return (1);
	return (0);
}

void	make_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		info->philo[i].id = i + 1;
		if (i % 2 == 0)
		{
			info->philo[i].first_fork = i;
			info->philo[i].second_fork = i - 1;
		}
		else
		{
			info->philo[i].first_fork = i - 1;
			info->philo[i].second_fork = i;
		}
		info->philo[i].info = info;
		info->philo[i].eat_done = 0;
		i++;
	}
	info->philo[0].second_fork = info->number_of_philo - 1;
}

int	init(t_info *info, char *argv[])
{
	if (make_info(info, argv) != 0)
		return (1);
	if (info->number_of_must_eat == 0)
		return (1);
	if (make_info_2(info) != 0)
		return (1);
	if (init_mutex(info) != 0)
	{
		free(info->lock);
		free(info->philo_thread);
		free(info->philo);
		return (1);
	}
	make_philo(info);
	return (0);
}
