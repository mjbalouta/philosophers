/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:34:05 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/22 17:19:22 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop == 0)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (check_stop(philo) == -1)
			return (NULL);
		eating(philo);
		if (check_stop(philo) == -1)
			return (NULL);
		print_log(philo->philo_id + 1, " is sleeping", philo->data);
		if (check_stop(philo) == -1)
			return (NULL);
		usleep(philo->data->time_to_sleep * 1000);
		if (check_stop(philo) == -1)
			return (NULL);
		print_log(philo->philo_id + 1, " is thinking", philo->data);
		if (philo->data->nr_philos % 2 != 0 && philo->philo_id % 2 != 0)
			usleep(1000);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}

int	handle_threads(t_data *data)
{
	pthread_t	*ids;
	t_philo		*philos;
	pthread_t	mon_id;

	ids = malloc(sizeof(pthread_t) * data->nr_philos);
	if (!ids)
		return (-1);
	philos = malloc(sizeof(t_philo) * data->nr_philos);
	if (!philos)
		return (-1);
	if (create_mutexes(data, philos) != 0)
		return (-2);
	if (create_threads(data, philos, ids, &mon_id) != 0)
		return (-2);
	join_threads(data, ids, &mon_id);
	destroy_mutexes(data, philos);
	free(philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		error_result;
	
	if (ac < 5 || ac > 6)
		return (write(2, "Error. Needs 4 or 5 args.\n", 26));
	error_result = handle_args(ac, av, &data);
	if (error_result == -1)
		return (write(2, "Error. Invalid arg.\n", 20));
	if (error_result == -2)
		return (write(2, "Error. Invalid malloc.\n", 23));
	handle_threads(&data);
	return (0);
}
 