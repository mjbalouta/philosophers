/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:34:35 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/24 16:49:06 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *nptr)
{
	int		i;
	int		negative;
	long	num;

	i = 0;
	num = 0;
	negative = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10;
		num = num + (nptr[i] - '0');
		i++;
	}
	if (negative == 1)
		return (-num);
	return (num);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	array[10];
	int		i;

	num = n;
	i = 0;
	if (num == 0)
		write (fd, "0", 1);
	if (num < 0)
	{
		num = -num;
		write(fd, "-", 1);
	}
	while (num > 0)
	{
		array[i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	i = i - 1;
	while (i >= 0)
		write(fd, &array[i--], 1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	check_and_print(int philo_id, char *str, t_philo *philo)
{
	if (check_stop(philo) == -1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (1);
	}
	print_log(philo_id, str, philo->data);
	return (0);
}

int	check_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (0);
}

// void	free_data(t_data *data)
// {
// 	if (data->philo_id)
// 		free(data->philo_id);
// 	if (data->forks)
// 		free(data->forks);
// }
