/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/21 14:31:42 by mjoao-fr         ###   ########.fr       */
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
		usleep(philo->data->time_to_die * 1000);
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
	gettimeofday(&current_time, NULL);
	philo->last_meal = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	philo->ate++;
	print_log(philo->philo_id + 1, " has taken a fork", philo->data);
	print_log(philo->philo_id + 1, " is eating", philo->data);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}

int	verify_if_all_ate(t_philo *philo)
{
	int	z;

	z = 0;
	if (philo[0].data->meals_defined == 1)
	{
		while (z < philo[0].data->nr_philos)
		{
			// printf("%d\n", philo[0].data->nr_meals);
			if (philo[0].data->nr_meals > philo[z].ate)
				return (0);
			z++;
		}	
		philo[0].data->stop = 1;
		return (-1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philo;
	struct timeval current_time;
	long time_passed;
	int	i;
	
	philo = (t_philo *)arg;
	if (philo[0].data->nr_philos == 1)
		return (NULL);
	while (philo[0].data->stop == 0)
	{
		i = 0;
		while(i < philo[0].data->nr_philos)
		{
			gettimeofday(&current_time, NULL);
			time_passed = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - philo[i].last_meal;
			if (time_passed > philo[0].data->time_to_die)
			{
				// printf("Last Meal: %ld\n", philo[i].last_meal);
				// printf("Time Passed: %ld\n", time_passed);
				// printf("Time to Die: %d\n", philo[0].data->time_to_die);
				philo[0].data->stop = 1;
				print_log(philo[i].philo_id + 1, " died", philo[0].data);
				return (NULL);
			}
			i++;
		}
		if (verify_if_all_ate(philo) == -1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
