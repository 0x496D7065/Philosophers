/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:08 by lpetit            #+#    #+#             */
/*   Updated: 2024/02/23 10:50:08 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	size_t	philo_nbr;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	tine_to_sleep;
	int	nbr_must_eat;
	int	id;
	pthread_t	philo;
	pthread_mutex_t	*left;
	pthread_mutex_t *right;
}		t_data;

int	ft_isdigit(const char *str);

#endif
