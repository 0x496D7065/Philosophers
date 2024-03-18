/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <lpetit@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:23:07 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/18 16:19:23 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_data *data)
{
	if (data->id % 2 == 0)
	{
		while (is_alive(data) == 0)
			if (*(data)->left_busy == 0)
				break;
		pthread_mutex_lock(data->left);
		*(data)->left_busy = 1;
		write_lock(data, 2);
		while (is_alive(data) == 0)
			if (data->right_busy == 0)
				break;
		pthread_mutex_lock(&data->right);
		data->right_busy = 1;
		write_lock(data, 2);
	}
	else
	{
		while (is_alive(data) == 0)
			if (data->right_busy == 0)
				break;
		pthread_mutex_lock(&data->right);
		data->right_busy = 1;
		write_lock(data, 2);
		while (is_alive(data) == 0)
			if (*(data)->left_busy == 0)
				break;
		pthread_mutex_lock(data->left);
		*(data)->left_busy = 1;
		write_lock(data, 2);
	}
}
