/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:54 by surkim            #+#    #+#             */
/*   Updated: 2023/08/31 11:22:05 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_philo;
	long			number_of_must_eat;
	long			start_time;
	int				die_flag;
	pthread_t		*philo_thread;
	pthread_mutex_t	*lock;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	tmp_lock;
	struct s_philo	*philo;
}t_info;

typedef struct s_philo
{
	int				id;
	int				first_fork;
	int				second_fork;
	int				eat_done;
	long			sleep_time;
	long			eat_time;
	t_info			*info;
}t_philo;

int		init(t_info *info, char *argv[]);
long	ft_atol(const char *str);
long	get_time(void);
int		check_die(t_info *info);
int		check_error(t_info *info);
void	print_get_fork(t_philo *philo);
void	until_sleep(long time, t_info *info);
int		pthread_start(t_info *info);
void	*philo_cycle(void *tmp);
void	ft_eating(t_philo *philo);
void	ft_sleeping(t_philo *philo);
void	ft_thinking(t_philo *philo);

#endif