/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 15:44:55 by lkarri            #+#    #+#             */
/*   Updated: 2021/10/26 10:57:48 by lkarri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_input_data	data;
	int				i;

	i = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of arguments\n");
		return (-1);
	}
	i = parse_and_init(&data, argv);
	if (i != 0)
	{
		if (i == 1)
			printf("All variables must be positive\n");
		if (i == 2)
			printf("Too few philosophers\n");
		return (-1);
	}
	simulation (&data);
	free(data.fork);
	free(data.philo_data);
	return (0);
}
