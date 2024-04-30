/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:23:07 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/28 14:49:46 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
