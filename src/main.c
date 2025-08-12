/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:34:05 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/10 15:47:41 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine(t_data *data)
{
	
}

void	handle_threads(int ac, t_data *data)
{
	pthread_t id;

	while (ac > 0)
	{
		if (pthread_create(&id, NULL, routine, data) != 0)
			return (write(2, "Error creating thread.\n", 23)); 
		pthread_join(&id, NULL);
	}
}

int	main(int ac, char **av)
{
	t_data data;
	
	if (ac < 5 || ac > 6)
		return (write(2, "Error. Needs 4 or 5 args.\n", 26));
	if (handle_args(ac, av, &data) == -1)
		return (write(2, "Error. Invalid arg.\n", 20));
	handle_threads(ac, &data);
	return (0);
}
 