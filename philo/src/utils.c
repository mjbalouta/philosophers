/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:34:35 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/20 21:04:47 by mjoao-fr         ###   ########.fr       */
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

void	print_log(int philo_id, char *str, t_data *data)
{
	size_t			size;
	struct timeval	current_time;
	long			time_passed;
	
	gettimeofday(&current_time, NULL);
	time_passed = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - data->start_time;
	pthread_mutex_lock(&data->write_mutex);
	size = ft_strlen(str);
	ft_putnbr_fd(time_passed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, str, size);
	write(1, "\n", 1);
	pthread_mutex_unlock(&data->write_mutex);
}

// void	free_data(t_data *data)
// {
// 	if (data->philo_id)
// 		free(data->philo_id);
// 	if (data->forks)
// 		free(data->forks);
// }
