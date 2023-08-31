/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surkim <surkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:36:30 by surkim            #+#    #+#             */
/*   Updated: 2023/08/30 10:23:37 by surkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_white(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	ans;
	long	flag;

	i = -1;
	flag = 1;
	ans = 0;
	while (str[++i])
		if (is_white(str[i]) == 0)
			break ;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (flag * ans);
		ans = ans * 10 + str[i] - '0';
		i++;
	}
	return (flag * ans);
}
