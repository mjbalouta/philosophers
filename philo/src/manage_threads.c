/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:52:03 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/27 14:16:11 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_mutexes(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (write(2, "Mutex error.\n", 13));
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (write(2, "Mutex error.\n", 13));
	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_mutex_init(&philos[i].meal_mutex, NULL) != 0)
			return (write(2, "Mutex error.\n", 13));
		i++;
	}
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (write(2, "Mutex error.\n", 13));
	return (0);
}

int	create_threads(t_data *data, t_philo *philos, pthread_t *ids,
					pthread_t *mon_id)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_lock(&data->stop_mutex);
		philos[i].data = data;
		philos[i].data->stop = 0;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_lock(&philos[i].meal_mutex);
		philos[i].ate = 0;
		philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		philos[i].philo_id = i;
		if (pthread_create(&ids[i], NULL, routine, &philos[i]) != 0)
			return (write(2, "Error creating thread.\n", 23));
		i++;
	}
	if (pthread_create(mon_id, NULL, monitoring, philos) != 0)
		return (write(2, "Error creating thread.\n", 23));
	return (0);
}

void	join_threads(t_data *data, pthread_t *ids, pthread_t *mon_id)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(ids[i], NULL);
		i++;
	}
	pthread_join(*mon_id, NULL);
}

void	destroy_mutexes(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_mutex);
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
}
