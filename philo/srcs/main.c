/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:45:22 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/20 17:02:00 by lpetit           ###   ########.fr       */
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
	//printf("philo_nbr = %ld\n", data[0].philo_nbr);
	//printf("last_philo = %ld\n", last_philo);
	while (i <= last_philo)
	{
		//printf("i = %ld\n", i);
		pthread_mutex_init(&data[i].right, NULL);
		data[i].right_busy = 0;
		i++;
	}
	data[0].left = &data[last_philo].right;
	data[0].left_busy = &data[last_philo].right_busy;
	i = 1;
	while (i <= last_philo)
	{
		data[i].left = &data[i - 1].right;
		data[i].left_busy = &data[i - 1].right_busy;
		i++;
	}
	/*i = 0;
	while (i <= last_philo)
	{
		printf("left = %p, right = %p, id = %d\n", data[i].left, &data[i].right, data[i].id);
		i++;
	}*/
}

void	init_philo(t_data *data, t_spec *spec, int argc, char **argv)
{
	size_t	i;
	//size_t	id;
	size_t	n;

	i = 0;
	n = ft_atol(argv[1]);
	spec->dead = 0;
	spec->start_time = 0;
	spec->data = data;
	spec->write_flag = 0;
	pthread_mutex_init(&spec->write, NULL);
	while (i < n)
	{
		data[i].philo_nbr = ft_atol(argv[1]);
		data[i].time_to_die = ft_atol(argv[2]);
		data[i].time_to_eat = ft_atol(argv[3]);
		data[i].time_to_sleep = ft_atol(argv[4]);
		data[i].id = i + 1;
		data[i].dead = &spec->dead;
		data[i].write = &spec->write;
		data[i].write_busy = &spec->write_flag;
		data[i].meal_eaten = 0;
		data[i].start_time = &spec->start_time;
		//printf("%p\n", data[i].start_time);
		i++;
	}
	if (argc == 6)
		spec->nbr_of_meal = ft_atol(argv[5]);
	else
		spec->nbr_of_meal = -1;
	//printf("-----------------------\n");
	init_forks(data);
}

int	create_philo_thread(t_data *data, t_spec *spec)
{
	size_t	i;
	size_t	n;
	size_t	last_philo;

	i = 0;
	last_philo = data[0].philo_nbr - 1;
	//printf("spec address = %p\n", &spec->dead);
	//printf("data address = %p\n", data->dead);
	while (i <= last_philo)
	{
		n = pthread_create(&data[i].philo, NULL, ph_routine, (void *)&data[i]);
		if (n != 0)
			return (1);
		i++;
	}
	n = pthread_create(&spec->thread, NULL, spec_routine, (void *)spec);
	if (n != 0)
		return (1);
	i = 0;
	while (i <= last_philo)
	{
		pthread_join(data[i].philo, NULL);
		i++;
	}
	pthread_join(spec->thread, NULL);
	//spec->start_time = get_time();
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
		//printf("%d\n", spec.dead);
		if (create_philo_thread(data, &spec) == 1)
		{
			printf("error\n");
			return (0);
		}
		//pthread_mutex_unlock(&spec.write);
	}
	return (0);
}
