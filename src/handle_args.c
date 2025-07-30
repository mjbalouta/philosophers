/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:13:34 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/07/30 15:50:41 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	convert_args_to_numbers(char **av, t_data *data)
{
	data->nr_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nr_meals = ft_atoi(av[5]);
}

int	detect_invalid_char(int ac, char **av)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (i < (ac - 1))
	{
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
	convert_args_to_numbers(av, data);
}