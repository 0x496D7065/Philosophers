/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:33:38 by lpetit            #+#    #+#             */
/*   Updated: 2024/05/05 13:23:27 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_spec(t_spec *spec, t_data *data)
{
	size_t	n;

	spec->dead_flag = 0;
	spec->data = data;
	n = pthread_mutex_init(&spec->write, NULL);
	if (n != 0)
		return (1);
	n = pthread_mutex_init(&spec->meal, NULL);
	if (n != 0)
	{
		pthread_mutex_destroy(&spec->write);
		return (1);
	}
	n = pthread_mutex_init(&spec->dead, NULL);
	if (n != 0)
	{
		pthread_mutex_destroy(&spec->write);
		pthread_mutex_destroy(&spec->meal);
		return (1);
	}
	return (0);
}

void	init_base(t_data *data, int argc, char **argv, int i)
{
	data->philo_nbr = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->id = i + 1;
	data->eating = 0;
	data->meal_eaten = 0;
	if (argc == 6)
		data->nbr_of_meal = ft_atol(argv[5]);
	else
		data->nbr_of_meal = -1;
}

void	destroy_all_mutex(t_data *data, t_spec *spec, int n)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&spec->write);
	pthread_mutex_destroy(&spec->meal);
	pthread_mutex_destroy(&spec->dead);
	while (i < n)
	{
		pthread_mutex_destroy(&data[i].right);
		i++;
	}
}

int	check_meal(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data[0].philo_nbr)
	{
		pthread_mutex_lock(data[0].meal);
		if (data[i].meal_eaten < data[0].nbr_of_meal
			|| data[0].nbr_of_meal == -1)
		{
			pthread_mutex_unlock(data[0].meal);
			return (0);
		}
		pthread_mutex_unlock(data[0].meal);
		i++;
		if (i == data[0].philo_nbr)
		{
			pthread_mutex_lock(data[0].dead)
			*data[0].dead_flag = 1;
			pthread_mutex_unlock(data[0].dead);
			return (1);
		}
	}
	return (0);
}

void	clean_threads(t_data *data, t_spec *spec, size_t n)
{
	size_t	i;

	i = 0;
	pthread_join(spec->thread, NULL);
	while (i < n)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
}
