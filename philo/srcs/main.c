/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:45:22 by lpetit            #+#    #+#             */
/*   Updated: 2024/04/28 16:54:05 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(argv[i]) == 1 || ft_atol(argv[i]) > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

void	init_forks(t_data *data)
{
	size_t	i;
	size_t	last_philo;

	i = 0;
	last_philo = data[0].philo_nbr - 1;
	while (i <= last_philo)
	{
		pthread_mutex_init(&data[i].right, NULL);
		i++;
	}
	data[0].left = &data[last_philo].right;
	i = 1;
	while (i <= last_philo)
	{
		data[i].left = &data[i - 1].right;
		i++;
	}
}

void	init_philo(t_data *data, t_spec *spec, int argc, char **argv)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_atol(argv[1]);
	spec->dead_flag = 0;
	spec->data = data;
	pthread_mutex_init(&spec->write, NULL);
	pthread_mutex_init(&spec->meal, NULL);
	pthread_mutex_init(&spec->dead, NULL);
	while (i < n)
	{
		data[i].philo_nbr = ft_atol(argv[1]);
		data[i].time_to_die = ft_atol(argv[2]);
		data[i].time_to_eat = ft_atol(argv[3]);
		data[i].time_to_sleep = ft_atol(argv[4]);
		data[i].id = i + 1;
		data[i].dead = &spec->dead;
		data[i].write = &spec->write;
		data[i].meal = &spec->meal;
		data[i].eating = 0;
		data[i].meal_eaten = 0;
		data[i].start_time = get_time();
		data[i].last_meal = data[i].start_time;
		data[i].dead_flag = &spec->dead_flag;
		if (argc == 6)
			data[i].nbr_of_meal = ft_atol(argv[5]);
		i++;
	}
	init_forks(data);
}

int	create_philo_thread(t_data *data, t_spec *spec)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = pthread_create(&spec->thread, NULL, spec_routine, (void *)data);
	if (n != 0)
		return (1);
	while (i < data[0].philo_nbr)
	{
		n = pthread_create(&data[i].philo, NULL, ph_routine, (void *)&data[i]);
		if (n != 0)
			return (1);
		i++;
	}
	i = 0;
	pthread_join(spec->thread, NULL);
	while (i < data[0].philo_nbr)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data[200];
	t_spec	spec;
	int	n;

	if (argc == 5 || argc == 6)
	{
		n = arg_check(argc, argv);
		if (n == 1)
		{
			printf("error\n");
			return (0);
		}
		init_philo(data, &spec, argc, argv);
		if (create_philo_thread(data, &spec) == 1)
		{
			printf("error\n");
			return (0);
		}
	}
	return (0);
}
