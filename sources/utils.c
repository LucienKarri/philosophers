/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:06:07 by lkarri            #+#    #+#             */
/*   Updated: 2021/10/26 00:03:01 by lkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	int		znak;
	long	num;
	long	output;

	i = 0;
	output = 0;
	znak = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		znak = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = str[i] - '0';
		output = output * 10 + num;
		i++;
	}
	return (output * znak);
}

long long	timestemp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long	timesdif(long long pres, long long past)
{
	return (pres - past);
}

void	sleeping_time(long long tt_sleep, t_input_data *data)
{
	long long	start;

	start = timestemp();
	while (data->died == 0)
	{
		if (timesdif(timestemp(), start) >= tt_sleep)
			break ;
		usleep (50);
	}
}

void	messages(t_input_data *data, int philo_id, char *arr)
{
	pthread_mutex_lock(&(data->message));
	if (data->died == 0)
		printf("%lld %d %s\n", timesdif(timestemp(), data->t_set),
			philo_id, arr);
	pthread_mutex_unlock(&(data->message));
	return ;
}
