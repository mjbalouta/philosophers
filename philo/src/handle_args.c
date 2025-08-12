/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:13:34 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/12 16:36:21 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	convert_initialize_data(char **av, t_data *data)
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	data->nr_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_defined = 0;
	if (av[5])
	{
		data->meals_defined = 1;
		data->nr_meals = ft_atoi(av[5]);
	}
	else
		data->nr_meals = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->forks)
		return (-1);
	data->stop = 0;
	data->start_time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
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
	if (detect_invalid_char(ac, av) == -1)
		return (-1);
	if (convert_initialize_data(av, data) == -1)
		return (-2);
	return (0);
}
