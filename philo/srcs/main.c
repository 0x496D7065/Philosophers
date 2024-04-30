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

int	init_forks(t_data *data, t_spec *spec)
{
	size_t	i;
	size_t	last_philo;

	i = 0;
	last_philo = data[0].philo_nbr - 1;
	while (i <= last_philo)
	{
		if (pthread_mutex_init(&data[i].right, NULL) != 0)
		{
			destroy_all_mutex(data, spec, i);
			return (1);
		}
		i++;
	}
	data[0].left = &data[last_philo].right;
	i = 1;
	while (i <= last_philo)
	{
		data[i].left = &data[i - 1].right;
		i++;
	}
	return (0);
}

int	init_philo(t_data *data, t_spec *spec, int argc, char **argv)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_atol(argv[1]);
	if (init_spec(spec, data) != 0)
		return (1);
	while (i < n)
	{
		init_base(&data[i], argc, argv, i);
		data[i].dead = &spec->dead;
		data[i].write = &spec->write;
		data[i].meal = &spec->meal;
		data[i].start_time = get_time();
		data[i].last_meal = data[i].start_time;
		data[i].dead_flag = &spec->dead_flag;
		i++;
	}
	if (init_forks(data, spec) != 0)
		return (1);
	return (0);
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

	if (argc == 5 || argc == 6)
	{
		if (arg_check(argc, argv) != 0)
		{
			printf("error\n");
			return (1);
		}
		if (init_philo(data, &spec, argc, argv) != 0)
		{
			printf("error\n");
			return (1);
		}
		if (create_philo_thread(data, &spec) == 1)
		{
			printf("error\n");
			return (1);
		}
		destroy_all_mutex(data, &spec, data[0].philo_nbr);
	}
	return (0);
}
