/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:34:05 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/19 23:38:50 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (philo->data->stop == 0)
	{
		eating(philo);
		if (philo->data->stop == 1)
            return (NULL);
		print_log(philo->philo_id + 1, " is sleeping", philo->data);
		usleep(philo->data->time_to_sleep * 1000);
		if (philo->data->stop == 1)
            return (NULL);
		print_log(philo->philo_id + 1, " is thinking", philo->data);
	}
	return (NULL);
}

int	handle_threads(t_data *data)
{
	int			i;
	pthread_t	*ids;
	t_philo		*philos;
	pthread_t	mon_id;

	ids = malloc(sizeof(pthread_t) * data->nr_philos);
	if (!ids)
		return (-1);
	philos = malloc(sizeof(t_philo) * data->nr_philos);
	if (!philos)
		return (-1);
	i = -1;
	while (++i < data->nr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (write(2, "Mutex error.\n", 13));	
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
        return (write(2, "Mutex error.\n", 13));
	i = -1;
	while (++i < data->nr_philos)
	{
		philos[i].data = data;
		philos[i].data->stop = 0;
		philos[i].ate = 0;
		philos[i].last_meal = data->start_time;
		philos[i].philo_id = i;
		if (pthread_create(&ids[i], NULL, routine, &philos[i]) != 0)
			return (write(2, "Error creating thread.\n", 23));
	}
	if (pthread_create(&mon_id, NULL, monitoring, philos) != 0)
		return (write(2, "Error creating thread.\n", 23));
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
	pthread_join(mon_id, NULL);
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
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
 