/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:49:27 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/09 14:00:34 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_av(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' || av[i][j] > '9') && j != 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_init_args(t_args *var, char **av)
{
	if (ft_check_av(av))
		return (throw_error());
	var->t_eat = 0;
	var->time = init_time();
	var->num_philo = ft_atoi(av[1]);
	var->time_die = ft_atoi(av[2]);
	var->time_eat = ft_atoi(av[3]);
	var->time_sleep = ft_atoi(av[4]);
	if (var->num_philo <= 0 || var->time_die <= 0
		|| var->time_eat <= 0 || var->time_sleep <= 0)
		return (0);
	if (av[5])
	{
		var->must_eat = ft_atoi(av[5]);
		if (var->must_eat <= 0)
			return (1);
	}
	else
		var->must_eat = -1;
	return (0);
}

static void	assign_data_each_philo(t_philo *philo, t_args *var,
	pthread_mutex_t *mut, pthread_mutex_t *ptr_m)
{
	int	i;

	i = 1;
	while (i <= var->num_philo)
	{
		philo[i].ate = 0;
		philo[i].id = i;
		philo[i].mutex = mut;
		philo[i].print = ptr_m;
		philo[i].info = var;
		i++;
	}
}

int	init_philo(t_args *var, t_philo *philo)
{
	pthread_mutex_t	*mutex;
	pthread_mutex_t	point_m;
	int				i;

	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * var->num_philo);
	if (!mutex || !philo)
		return (free_param(philo, mutex, var));
	while (i < var->num_philo)
		if (pthread_mutex_init(&mutex[i++], NULL))
			return (free_param(philo, mutex, var));
	if (pthread_mutex_init(&point_m, NULL))
		return (free_param(philo, mutex, var));
	assign_data_each_philo(philo, var, mutex, &point_m);
	return (0);
}
