/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:29:01 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/10/24 16:48:49 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_timestamp(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	smart_sleep(t_philo *philo, long sleep_time)
{
	long	start;
	long	full_sleep;

	start = get_timestamp();
	full_sleep = start + sleep_time;
	while (get_timestamp() < full_sleep)
	{
		if (check_stop(philo) == -1)
			return (1);
		usleep(1000);
	}
	return (0);
}

int	print_log(int philo_id, char *str, t_data *data)
{
	size_t			size;
	struct timeval	current_time;
	long			time_passed;

	gettimeofday(&current_time, NULL);
	time_passed = (get_timestamp()) - data->start_time;
	pthread_mutex_lock(&data->write_mutex);
	size = ft_strlen(str);
	ft_putnbr_fd(time_passed, 1);
	write(1, " ", 1);
	ft_putnbr_fd(philo_id, 1);
	write(1, str, size);
	write(1, "\n", 1);
	pthread_mutex_unlock(&data->write_mutex);
	return (0);
}
