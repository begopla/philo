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

void	philo_eats(t_philo *philo)
{
	t_args *args;

	args = philo->args;
	pthread_mutex_lock(&(args->forks[philo->left_fork_id]));
	action_print(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->forks[philo->right_fork_id]));
	action_print(args, philo->id, "has taken a fork");
	pthread_mutex_lock(&(args->meal_check));
	action_print(args, philo->id, "is eating");
	philo->last_meal = init_time();
	pthread_mutex_unlock(&(args->meal_check));
	smart_sleep(args->time_eat, args);
	(philo->ate)++;
	pthread_mutex_unlock(&(args->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(args->forks[philo->right_fork_id]));
}


void	*p_thread(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_args	*args;

	i = 0;
	philo = (t_philo *)void_philo;
	args = philo->args;
	if (philo->id % 2)
		usleep(15000);
	while (!(args->died))
	{
		philo_eats(philo);
		if (args->all_eat)
			break ;
		action_print(args, philo->id, "is sleeping");
		smart_sleep(args->time_sleep, args);
		action_print(args, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}


void	death_checker(t_args *arg, t_philo *p)
{
	int i;

	while (!(arg->all_eat))
	{
		i = -1;
		while (++i < arg->num_philo && !(arg->died))
		{
			pthread_mutex_lock(&(arg->meal_check));
			if (time_diff(p[i].last_meal, init_time()) > arg->time_die)
			{
				action_print(arg, i, "died");
				arg->died = 1;
			}
			pthread_mutex_unlock(&(arg->meal_check));
			if (arg->died == 1)
				break ;
			usleep(100);
		}
		if (arg->died)
			break ;
		i = 0;
		while (arg->nb_eat != -1 && i < arg->num_philo && p[i].ate >= arg->nb_eat)
			i++;
		if (i == arg->num_philo)
			arg->all_eat = 1;
	}
}

int		launcher(t_args *args)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = args->philosophers;
	args->first_timestamp = init_time();
	while (i < args->num_philo)
	{
		if (pthread_create(&(phi[i].thread_id), NULL, p_thread, &(phi[i])))
			return (1);
		phi[i].last_meal = init_time();
		i++;
	}
	death_checker(args, args->philosophers);
	exit_launcher(args, phi);
	return (0);
}
