/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:14:53 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/24 16:49:37 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_if_time_to_die(long time_passed, t_philo *philo)
{
	if (time_passed > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo[0].data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		print_log(philo->philo_id + 1, "\e[0;31m died", philo->data);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	long	time_passed;
	int		i;

	philo = (t_philo *)arg;
	while (check_stop(philo) == 0)
	{
		i = -1;
		while (++i < philo[0].data->nr_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			time_passed = (get_timestamp()) - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if (check_if_time_to_die(time_passed, &philo[i]) == 1)
				return (NULL);
		}
		if (verify_if_all_ate(philo) == -1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
