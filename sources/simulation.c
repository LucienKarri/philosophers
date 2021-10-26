/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 17:57:58 by lkarri            #+#    #+#             */
/*   Updated: 2021/10/26 12:26:04 by lkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philosopher_data *philo)
{
	t_input_data	*data;

	data = philo->input;
	pthread_mutex_lock(&(data->fork[philo->left_fork]));
	messages(data, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(data->fork[philo->right_fork]));
	messages(data, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&(data->last_meal));
	messages(data, philo->philo_id, "is eating");
	philo->last_meal = timestemp();
	pthread_mutex_unlock(&(data->last_meal));
	sleeping_time(data->tt_eat, data);
	(philo->ate)++;
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*life_cycle(void *input)
{
	t_philosopher_data	*philo;
	t_input_data		*data;
	int					i;

	philo = (t_philosopher_data *)input;
	data = philo->input;
	i = 0;
	if (philo->philo_id % 2)
		usleep(15000);
	while (data->died == 0)
	{
		eating(philo);
		if (data->ate == 1)
			break ;
		messages(data, philo->philo_id, "is sleeping");
		sleeping_time(data->tt_sleep, data);
		messages(data, philo->philo_id, "is thinking");
		i++;
	}
	return (NULL);
}

void	monitor(t_input_data *data, t_philosopher_data *philo)
{
	int					i;

	while (data->ate == 0)
	{
		i = -1;
		while (data->num_of_phils > ++i && data->died == 0)
		{
			pthread_mutex_lock(&(data->last_meal));
			if (timesdif(timestemp(), philo[i].last_meal) > data->tt_die)
			{
				messages(data, philo[i].philo_id, "died");
				data->died = 1;
			}
			pthread_mutex_unlock(&(data->last_meal));
			usleep(100);
		}
		if (data->died != 0)
			break ;
		i = 0;
		while (data->num_of_meal != -1 && data->num_of_phils > i
			&& philo[i].ate >= data->num_of_meal)
			i++;
		if (i == data->num_of_phils)
			data->ate = 1;
	}
}

int	simulation(t_input_data *data)
{
	int					i;
	t_philosopher_data	*philo;

	i = 0;
	philo = data->philo_data;
	data->t_set = timestemp();
	while (data->num_of_phils > i)
	{
		pthread_create(&(philo[i].thread_id), NULL, life_cycle, &philo[i]);
		philo[i].last_meal = timestemp();
		i++;
	}
	monitor(data, philo);
	destroy_mutex(data);
	return (1);
}
