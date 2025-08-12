/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/12 16:40:07 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	struct timeval current_time;
	int	left;
	int	right;

	left = philo->philo_id;
	right = (philo->philo_id + 1) % philo->data->nr_philos;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_log(philo->philo_id, " has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_log(philo->philo_id, " has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
	}
	print_log(philo->philo_id, " has taken a fork");
	print_log(philo->philo_id, " is eating");
	usleep(philo->data->time_to_eat * 1000);
	gettimeofday(&current_time, NULL);
	philo->last_meal = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	philo->ate++;
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}
void	*monitoring(void *arg)
{
	t_philo	*philo;
	struct timeval current_time;
	int time_passed;
	int	i;
	
	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		while(philo->data->stop == 0)
		{
			gettimeofday(&current_time, NULL);
			time_passed = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - philo->data->start_time;
			if (time_passed - philo[i].last_meal > philo->data->time_to_die)
			{
				philo->data->stop = 1;
				break;
			}
			if (philo->data->meals_defined == 1)
			{
				if (philo->data->nr_meals == philo->ate)
				{
					philo->data->stop = 1;
					break;
				}
			}
			i++;
		}
	}
	return (NULL);
}
