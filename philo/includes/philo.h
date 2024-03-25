/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:08 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/25 14:33:30 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data
{
	size_t	philo_nbr;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	last_meal;
	int	id;
	int	meal_eaten;
	int	*dead;
	int	*write_busy;
	size_t	*start_time;
	pthread_t	philo;
	pthread_mutex_t	*left;
	int	*left_busy;
	pthread_mutex_t right;
	int	right_busy;
	pthread_mutex_t	*write;
}		t_data;

typedef struct s_spectator
{
	int	dead;
	int	nbr_of_meal;
	int	write_flag;
	size_t	start_time;
	t_data *data;
	pthread_t	thread;
	pthread_mutex_t	write;
}	t_spec;

void	take_fork_one(t_data *data);
void	take_fork_two(t_data *data);
void	take_both_forks(t_data *data);
void	write_lock(t_data *data, int c);

void	*ph_routine(void *data);
void	*spec_routine(void *spec);

int	ft_isdigit(const char *str);
int	ft_usleep(size_t time);
int	is_alive(t_data *data);

size_t	ft_strlen(const char *str);
size_t	get_time(void);
long long	ft_atol(const char *nptr);

#endif
