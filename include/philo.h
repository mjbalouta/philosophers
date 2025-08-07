/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:33:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/07 12:11:46 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int	nr_philos;
	int	time_to_die;
	int	time_to_eat;
	int time_to_sleep;
	int	nr_meals;
}				t_data;


int		handle_args(int ac, char **av, t_data *data);
long	ft_atoi(const char *nptr);
int		detect_invalid_char(int ac, char **av);

#endif