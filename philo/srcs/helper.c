/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:48:44 by lpetit            #+#    #+#             */
/*   Updated: 2024/03/10 12:35:18 by lpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	ft_isdigit(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

long long	ft_atol(const char *nptr)
{
	int		sign;
	long long		nbr;

	sign = 0;
	nbr = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			sign++;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		nbr = (nbr * 10) + (*nptr - 48);
		nptr++;
	}
	if ((sign % 2) > 0)
		nbr = -nbr;
	return (nbr);
}

int	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(1000);
	return (0);
}

size_t	get_time(void)
{
	struct timeval time;
	char	*msg;

	msg = "gettime error\n";
	if (gettimeofday(&time, NULL) == -1)
		write(2, &msg, ft_strlen(msg));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
