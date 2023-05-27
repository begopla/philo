/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:10 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/09 13:50:54 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	ft_free_struc(t_philo *philo, pthread_mutex_t *m, t_args *var)
{
	if (philo)
		free(philo);
	if (m)
		free(m);
	if (var)
		free(var);
	return (1);
}

void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->info->num_philo > i)
		pthread_mutex_destroy(&philo->mutex[i++]);
}

unsigned long	init_time(void)
{
	struct timeval	time;
	unsigned long	total;
	unsigned long	sec;
	unsigned long	usec;

	gettimeofday(&time, NULL);
	sec = (time.tv_sec * 1000);
	usec = (time.tv_usec * 1000);
	total = sec + usec;
	return (total);
}

unsigned long	return_time(t_philo *philo)
{
	return (init_time() - philo->info->time);
}
