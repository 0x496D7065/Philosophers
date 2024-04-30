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
