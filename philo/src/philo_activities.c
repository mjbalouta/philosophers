/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:50:10 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/22 17:33:40 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
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
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 1;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return ;
	}
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_log(philo->philo_id + 1, " has taken a fork", philo->data);
		if (check_stop(philo) == -1)
			return ;
		pthread_mutex_lock(&philo->data->forks[right]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_log(philo->philo_id + 1, " has taken a fork", philo->data);
		if (check_stop(philo) == -1)
			return ;
		pthread_mutex_lock(&philo->data->forks[left]);
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_timestamp();
	philo->ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (check_stop(philo) == -1)
		return ;
	print_log(philo->philo_id + 1, " has taken a fork", philo->data);
	print_log(philo->philo_id + 1, " is eating", philo->data);
	if (check_stop(philo) == -1)
		return ;
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
			pthread_mutex_lock(&philo[z].meal_mutex);
			if (philo[0].data->nr_meals > philo[z].ate)
			{
				pthread_mutex_unlock(&philo[z].meal_mutex);
				return (0);
			}
			pthread_mutex_unlock(&philo[z].meal_mutex);
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
	long time_passed;
	int	i;
	
	philo = (t_philo *)arg;
	if (check_stop(philo) == -1)
		return (NULL);
	while (philo[0].data->stop == 0)
	{
		i = -1;
		while(++i < philo[0].data->nr_philos)
		{
			pthread_mutex_lock(&philo[i].meal_mutex);
			time_passed = (get_timestamp()) - philo[i].last_meal;
			pthread_mutex_unlock(&philo[i].meal_mutex);
			if (time_passed > philo[i].data->time_to_die)
			{
				pthread_mutex_lock(&philo[0].data->stop_mutex);
				philo[0].data->stop = 1;
				pthread_mutex_unlock(&philo[0].data->stop_mutex);
				print_log(philo[i].philo_id + 1, " died", philo[0].data);
				return (NULL);
			}
		}
		if (verify_if_all_ate(philo) == -1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
