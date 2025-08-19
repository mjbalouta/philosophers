/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoao-fr <mjoao-fr@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:33:24 by mjoao-fr          #+#    #+#             */
/*   Updated: 2025/08/19 14:21:56 by mjoao-fr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_meals;
	pthread_mutex_t	*forks;
	int				stop;
	int				meals_defined;	
	long			start_time;	
}				t_data;


typedef struct s_philo
{
	int			philo_id;
	long		last_meal;
	int			ate;
	t_data		*data;
	
}				t_philo;

int		init_data(char **av, t_data *data);
int		handle_args(int ac, char **av, t_data *data);
long	ft_atoi(const char *nptr);
void	ft_putnbr_fd(int n, int fd);
size_t	ft_strlen(const char *s);
void	print_log(int philo_id, char *str);
int		detect_invalid_char(int ac, char **av);
int		handle_threads(t_data *data);
void	*routine(void *arg);
void	eating(t_philo *philo);
void	*monitoring(void *arg);
void	free_data(t_data *data);

#endif