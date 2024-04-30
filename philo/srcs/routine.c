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

void	*spec_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (is_philo_dead(data) == 1)
			break ;
	}
	return (NULL);
}
