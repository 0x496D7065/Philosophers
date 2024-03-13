/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:08 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/13 17:49:10 by lpetit           ###   ########.fr       */
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
	size_t	nbr_of_meal;
	size_t	meal_eaten;
	size_t	last_meal;
	int	id;
	int	*dead;
	size_t	*start_time;
	pthread_t	philo;
	pthread_mutex_t	*left;
	pthread_mutex_t right;
	pthread_mutex_t	*write;
}		t_data;

typedef struct s_spectator
{
	int	dead;
	size_t	start_time;
	pthread_t	thread;
	pthread_mutex_t	write;
}	t_spec;

void	*ph_routine(void *data);
void	*spec_routine(void *spec);

int	ft_isdigit(const char *str);
int	ft_usleep(size_t time);
size_t	ft_strlen(const char *str);
size_t	get_time(void);
long long	ft_atol(const char *nptr);

#endif
