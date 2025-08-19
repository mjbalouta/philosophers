/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/19 23:44:49 by mjoao-fr         ###   ########.fr       */
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
	if (philo->data->nr_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_log(philo->philo_id + 1, " has taken a fork", philo->data);
		pthread_mutex_unlock(&philo->data->forks[left]);
		usleep(philo->data->time_to_die);
		print_log(philo->philo_id + 1, " died", philo->data);
		philo->data->stop = 1;
		return ;
	}
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_log(philo->philo_id + 1, " has taken a fork", philo->data);
		pthread_mutex_lock(&philo->data->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_log(philo->philo_id + 1, " has taken a fork", philo->data);
		pthread_mutex_lock(&philo->data->forks[left]);
	}
	print_log(philo->philo_id + 1, " has taken a fork", philo->data);
	print_log(philo->philo_id + 1, " is eating", philo->data);
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
	if (philo[0].data->nr_philos == 1)
		return (NULL);
	while (1)
	{
		i = 0;
		while(i < philo[0].data->nr_philos && philo[0].data->stop == 0)
		{
			gettimeofday(&current_time, NULL);
			time_passed = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - philo->data->start_time;
			if (time_passed - philo[i].last_meal > philo[0].data->time_to_die)
			{
				philo[0].data->stop = 1;
				print_log(philo[i].philo_id + 1, " died", philo[0].data);
				break;
			}
			if (philo[0].data->meals_defined == 1)
			{
				if (philo[0].data->nr_meals == philo[i].ate)
				{
					philo[0].data->stop = 1;
					return (NULL);
				}
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
