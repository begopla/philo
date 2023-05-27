/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:49:27 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/18 12:25:36 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_args *args)
{
	int	i;

	i = args->num_philo;
	while (--i >= 0)
	{
		args->philosophers[i].id = i;
		args->philosophers[i].ate = 0;
		args->philosophers[i].left_fork_id= i;
		args->philosophers[i].right_fork_id = (i + 1) % args->num_philo;
		args->philosophers[i].last_meal = 0;
		args->philosophers[i].args = args;
	}
	return (0);
}

int	init_mutex(t_args *args)
{
	int i;

	i = args->num_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(args->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(args->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(args->meal_check), NULL))
		return (1);
	return (0);
}


int	ft_init_all(t_args *args, char **av)
{
	args->num_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	args->all_eat = 0;
	args->died = 0;
	if (args->num_philo <= 0 || args->time_die < 60
		|| args->time_eat < 60 || args->time_sleep < 60 || args->num_philo > 200)
		return (1);
	if (av[5])
	{
		args->nb_eat = ft_atoi(av[5]);
		if (args->nb_eat <= 0)
			return (1);
	}
	else
		args->nb_eat = -1;
	if (init_mutex(args))
		return (2);
	init_philo(args);
	return (0);
}
