/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:01:24 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/28 15:59:11 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_or_think(t_data *data, int c)
{
	if (c == 0)
		output_status(data, "is thinking");
	else if (c == 1)
	{
		output_status(data, "is sleeping");
		ft_usleep(data->time_to_sleep);
	}
	return ;
}

int	check_dead(t_data *data)
{
	pthread_mutex_lock(data->dead);
	if (*data->dead_flag == 1)
	{
		pthread_mutex_unlock(data->dead);
		return (1);
	}
	pthread_mutex_unlock(data->dead);
	return (0);
}

void	philo_eat(t_data *data)
{
	pthread_mutex_lock(&data->right);
	output_status(data, "has taken a fork");
	pthread_mutex_lock(data->left);
	output_status(data, "has taken a fork");
	data->eating = 1;
	output_status(data, "is eating");
	pthread_mutex_lock(data->meal);
	data->last_meal = get_time();
	data->nbr_of_meal++;
	pthread_mutex_unlock(data->meal);
	ft_usleep(data->time_to_eat);
	data->eating = 0;
	pthread_mutex_unlock(&data->right);
	pthread_mutex_unlock(data->left);
	return ;
}
void	*ph_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->id % 2 == 0)
		ft_usleep(2);
	while (!check_dead(data))
	{
		philo_eat(data);
		sleep_or_think(data, 1);
		sleep_or_think(data, 0);
	}
	return ((void *)0);
}

int	timer_cmp(t_data *data)
{
	pthread_mutex_lock(data->meal);
	if (get_time() - data->last_meal >= data->time_to_die
		&& data->eating == 0)
	{
		pthread_mutex_unlock(data->meal);
		return (1);
	}
	pthread_mutex_unlock(data->meal);
	return (0);
}

int	is_philo_dead(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data[0].philo_nbr)
	{
		if (timer_cmp(&data[i]))
		{
			output_status(&data[i], "died");
			pthread_mutex_lock(data[0].dead);
			*data->dead_flag = 1;
			pthread_mutex_unlock(data[0].dead);
			return (1);
		}
		i++;
	}
	return (0);
}

void	output_status(t_data *data, char *str)
{
	size_t	timestamp;

	pthread_mutex_lock(data->write);
	timestamp = get_time() - data->start_time;
	if (!check_dead(data))
		printf("%ld %d %s\n", timestamp, data->id, str);
	pthread_mutex_unlock(data->write);
	return ;
}

void	*spec_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;
	while(1)
	{
		if (is_philo_dead(data) == 1)
			break;
	}
	return (NULL);
}
