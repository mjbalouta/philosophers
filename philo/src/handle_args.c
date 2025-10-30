/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:13:34 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/27 12:04:47 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(char **av, t_data *data)
{
	data->nr_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	if (data->nr_philos <= 0 || data->time_to_die <= 0)
		return (-1);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_defined = 0;
	if (av[5])
	{
		data->meals_defined = 1;
		data->nr_meals = ft_atoi(av[5]);
		if (data->nr_meals == 0)
			data->nr_meals = -1;
	}
	else
		data->nr_meals = 0;
	if (data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| data->nr_meals < 0)
		return (-1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->forks)
		return (-2);
	data->stop = 0;
	data->start_time = get_timestamp();
	return (0);
}

int	detect_invalid_char(int ac, char **av)
{
	int	i;
	int	z;

	i = 1;
	while (i < ac)
	{
		z = 0;
		while (av[i][z])
		{
			if (!(av[i][z] >= '0' && av[i][z] <= '9'))
				return (-1);
			z++;
		}
		i++;
	}
	return (0);
}

int	handle_args(int ac, char **av, t_data *data)
{
	int	error;

	if (detect_invalid_char(ac, av) == -1)
		return (-1);
	error = init_data(av, data);
	if (error != 0)
		return (error);
	return (0);
}
