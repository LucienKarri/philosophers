/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:45:11 by lkarri            #+#    #+#             */
/*   Updated: 2021/10/26 00:04:44 by lkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher_data
{
	int					philo_id;
	int					ate;
	int					left_fork;
	int					right_fork;
	long long			last_meal;
	struct s_input_data	*input;
	pthread_t			thread_id;
}				t_philosopher_data;

typedef struct s_input_data
{
	int					num_of_phils;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					num_of_meal;
	int					died;
	int					ate;	
	long long			t_set;
	pthread_mutex_t		message;
	pthread_mutex_t		last_meal;
	pthread_mutex_t		*fork;
	t_philosopher_data	*philo_data;
}				t_input_data;

int			ft_atoi(char *str);
long long	timestemp(void);
long long	timesdif(long long pres, long long past);
void		sleeping_time(long long tt_sleep, t_input_data *data);
void		messages(t_input_data *data, int philo_id, char *arr);
int			parse_and_init(t_input_data *data, char **argv);
void		init_philosopher(t_input_data *data);
void		init_mutex(t_input_data *data);
void		destroy_mutex(t_input_data *data);
int			simulation(t_input_data *data);
void		monitor(t_input_data *data, t_philosopher_data *philo);
void		*life_cycle(void *input);
void		eating(t_philosopher_data *philo);

#endif