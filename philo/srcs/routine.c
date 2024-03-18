/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:01:24 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/18 16:24:13 by lpetit           ###   ########.fr       */
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
		data->last_meal = get_time() - *(data)->start_time;
		ft_usleep(data->time_to_eat);
		*(data)->left_busy = 0;
		data->right_busy = 0;
		pthread_mutex_unlock(data->left);
		pthread_mutex_unlock(&data->right);
		data->meal_eaten += 1;
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
		pthread_mutex_lock(data->write);
		//printf("last_meal = %ld  ID=%d\n", data->last_meal, data->id);
		//printf("result = %ld  ID=%d\n", timestamp - data->last_meal, data->id);
		//printf("time_to_die= %ld  ID=%d\n", data->time_to_die, data->id);
		//printf("----------------\n");
		//printf("data address = %p\n", data->dead);
		timestamp = get_time() - *(data)->start_time;
		printf("%ld %d died\n", timestamp, data->id);
		//pthread_mutex_unlock(data->write);
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
	{
	}
	data->last_meal = get_time() - *(data)->start_time;
	//printf("start_time = %ld\n", *(data)->start_time);
	//printf("in data routine = %p\n", data->dead);
	while (1)
	{
		take_forks(data);
		write_lock_eatNsleep(data, 1);
		write_lock_eatNsleep(data, 2);
		write_lock(data, 1);
	}
	return ((void *)0);
}

void	*spec_routine(void *arg)
{
	t_spec *spec;
	int	i;
	int	last_philo;

	spec = (t_spec *)arg;
	spec->start_time = get_time();
	//printf("in spec address = %p\n", &spec->dead);
	//printf("%ld\n", spec->start_time);
	last_philo = spec->data[0].philo_nbr - 1;
	while(1)
	{
		i = 0;
		while (i <= last_philo && spec->nbr_of_meal != -1)
		{
			if (spec->data[i].meal_eaten >= spec->nbr_of_meal)
				i++;
			else
				break;
		}
		if (spec->dead == 1)
		{
			//printf("dead = %d\n", spec->dead);
			break;
		}
	}
	return (NULL);
}
