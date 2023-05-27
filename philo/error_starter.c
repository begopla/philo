/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:10 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/18 09:21:50 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	throw_error(int error)
{
	if (error == 1)
		printf("Error: Wrong params, please enter: num_of_philo\
		time_to_die time_to_eat time_to_sleep\
		(num_of_must_eat)\n ");
	else if (error == 2)
		printf("Error: Fatal error when inititalizing mutex\n");
	return (1);
}

void	exit_launcher(t_args *args, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < args->num_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < args->num_philo)
		pthread_mutex_destroy(&(args->forks[i]));
	pthread_mutex_destroy(&(args->writing));
}


void		smart_sleep(long long time, t_args *args)
{
	long long i;

	i = init_time();
	while (!(args->died))
	{
		if (time_diff(i, init_time()) >= time)
			break ;
		usleep(50);
	}
}
