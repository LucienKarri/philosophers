/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:24:45 by lkarri            #+#    #+#             */
/*   Updated: 2021/10/26 10:57:14 by lkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_input_data *data)
{
	int	i;

	i = 0;
	while (data->num_of_phils > i)
	{
		pthread_join(data->philo_data[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (data->num_of_phils > i)
	{
		pthread_mutex_destroy(&(data->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->message));
	pthread_mutex_destroy(&(data->last_meal));
}

void	init_mutex(t_input_data *data)
{
	int	i;

	i = 0;
	data->fork = (pthread_mutex_t *)malloc(sizeof(*(data->fork))
			* data->num_of_phils);
	while (data->num_of_phils > i)
	{
		pthread_mutex_init(&(data->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(data->message), NULL);
	pthread_mutex_init(&(data->last_meal), NULL);
}

void	init_philosopher(t_input_data *data)
{
	int	i;

	i = 0;
	data->philo_data = (t_philosopher_data *)malloc(sizeof(*(data->philo_data))
			* data->num_of_phils);
	while (data->num_of_phils > i)
	{
		data->philo_data[i].input = data;
		data->philo_data[i].ate = 0;
		data->philo_data[i].philo_id = i + 1;
		data->philo_data[i].left_fork = i;
		if (i + 1 == data->num_of_phils)
			data->philo_data[i].right_fork = 0;
		else
			data->philo_data[i].right_fork = i + 1;
		i++;
	}
}

int	parse_and_init(t_input_data *data, char **argv)
{
	data->num_of_phils = ft_atoi(argv[1]);
	data->tt_die = ft_atoi(argv[2]);
	data->tt_eat = ft_atoi(argv[3]);
	data->tt_sleep = ft_atoi(argv[4]);
	data->num_of_meal = 0;
	if (argv[5])
		data->num_of_meal = ft_atoi(argv[5]);
	if (data->num_of_phils < 2)
		return (2);
	if (data->num_of_meal < 0 || data->tt_die < 0
		|| data->tt_eat < 0 || data->tt_sleep < 0)
		return (1);
	if (!argv[5])
		data->num_of_meal = -1;
	data->died = 0;
	data->ate = 0;
	init_mutex(data);
	init_philosopher(data);
	return (0);
}
