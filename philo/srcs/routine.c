/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:01:24 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/13 17:47:42 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_lock(t_data *data, int c)
{
	size_t	timestamp;

	pthread_mutex_lock(data->write);
	timestamp = get_time() - *(data)->start_time;
	if (c == 1)
		printf("%ld %d is thinking\n", timestamp, data->id);
	else if (c == 2)
		printf("%ld %d has taken a fork\n", timestamp, data->id);
	pthread_mutex_unlock(data->write);
}

void	write_lock_eatNsleep(t_data *data, int c)
{
	size_t	timestamp;

	pthread_mutex_lock(data->write);
	timestamp = get_time() - *(data)->start_time;
	if (c == 1)
	{
		printf("%ld %d is eating\n", timestamp, data->id);
		pthread_mutex_unlock(data->write);
		ft_usleep(data->time_to_eat);
		data->meal_eaten += 1;
		data->last_meal = get_time() - *(data)->start_time;
	}
	else if (c == 2)
	{
		printf("%ld %d is sleeping\n", timestamp, data->id);
		pthread_mutex_unlock(data->write);
		ft_usleep(data->time_to_sleep);
	}
}

int	is_alive(t_data *data)
{
	size_t	timestamp;
	
	timestamp = get_time() - *(data)->start_time;
	//printf("in isalive\n");
	if ((timestamp - data->last_meal) > data->time_to_die)
	{
		printf("last_meal = %ld  ID=%d\n", data->last_meal, data->id);
		printf("result = %ld  ID=%d\n", timestamp - data->last_meal, data->id);
		printf("time_to_die= %ld  ID=%d\n", data->time_to_die, data->id);
		printf("----------------\n");
		printf("data address = %p\n", data->dead);
		pthread_mutex_lock(data->write);
		timestamp = get_time() - *(data)->start_time;
		printf("%ld %d died\n", timestamp, data->id);
		pthread_mutex_unlock(data->write);
		*(data)->dead = 1;
		return (1);
	}
	return (0);
}

void	*ph_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (*(data)->start_time == 0)
	data->last_meal = get_time() - *(data)->start_time;
	printf("start_time = %ld\n", *(data)->start_time);
	while (1)
	{
		printf("test\n");
		pthread_mutex_lock(data->left);
		printf("test\n");
		is_alive(data);
		write_lock(data, 2);
		while (data->left == &data->right)
			if (is_alive(data))
			{
				printf("through here\n");
				break;
			}
		pthread_mutex_lock(&data->right);
		is_alive(data);
		write_lock(data, 2);
		write_lock_eatNsleep(data, 1);
		pthread_mutex_unlock(data->left);
		pthread_mutex_unlock(&data->right);
		write_lock_eatNsleep(data, 2);
		write_lock(data, 1);
	}
	return (NULL);
}

void	*spec_routine(void *arg)
{
	t_spec *spec;

	spec = (t_spec *)arg;
	//spec->start_time = get_time();
	printf("in spec address = %p\n", spec->dead_flag);
	//printf("%ld\n", spec->start_time);
	while(1)
	{
		if (spec->dead == 1)
		{
			printf("dead = %d\n", *(spec)->dead_flag);
			break;
		}
	}
	return (NULL);
}
