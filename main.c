/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:23:49 by surkim            #+#    #+#             */
/*   Updated: 2023/08/31 11:20:42 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check(char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i <= 5)
	{
		if (argv[i] == NULL)
			break ;
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		if (j > 10)
			return (1);
		i++;
	}
	return (0);
}

void	all_free(t_info *info)
{
	free(info->lock);
	free(info->philo_thread);
	free(info->philo);
}

int	case_1(t_info *info)
{
	printf("0ms 1 has taken a fork\n");
	usleep(info->time_to_die * 1000);
	printf("%ldms 1 died\n", info->time_to_die);
	all_free(info);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc < 5 || argc > 6)
		return (1);
	if (check(argv) != 0)
		return (1);
	if (init(&info, argv) != 0)
		return (1);
	if (info.number_of_philo == 1)
		return (case_1(&info));
	if (pthread_start(&info) != 0)
	{
		all_free(&info);
		return (1);
	}
	all_free(&info);
	return (0);
}
