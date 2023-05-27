/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:46:07 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/09 14:08:47 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	throw_error(void)
{
	printf("Wrong params, please enter: num_of_philo\
	time_to_die time_to_eat time_to_sleep\
	 (num_of_must_eat)\n ");
	return (1);
}

void	ft_print(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("%lums	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

void	func(t_philo *philo, t_args *args)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].info->t_eat == philo[i].info->num_philo)
		{
			destroy_mutex(philo);
			ft_free_struc(philo, philo->mutex, args);
			return ;
		}
		if (return_time() - philo[i].last_meal
			> (unsigned long)args->time_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			ft_print("%lums	%d died", return_time(philo), philo->id);
			destroy_mutex(philo);
			ft_free_struc(philo, philo->mutex, args);
			return ;
		}
		i = (i + 1) % args->num_philo;
		usleep(500);
	}
}

void	*doSomething(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->id % 2 == 0)
		usleep(10); // let´s start by unevene philosofers
	philo->last_meal = init_time(); // we init the last meal to current time
	while (1)
	{
		printf("philosofer id resource I am locking: %d\n", philo->id - 1);
		pthread_mutex_lock(&philo->mutex[philo->id - 1]); // we lock the mutex from previous id, first philosofer to take the fork
		//We can now take a fork print has taken a fork message;
		ft_print(philo, return_time(philo), "has taken a fork");
		printf("philosofer id resource I am locking: %d\n", philo->id % philo->info->num_philo);
		pthread_mutex_lock(&philo->mutex[philo->id % philo->info->num_philo]); // we lock the next philosofer, to take the next form
		ft_print(philo, return_time(philo), "has taken a fork");
		ft_print(philo, return_time(philo), "is eating");
		philo->ate++;
		if (philo->ate == philo->info->must_eat)
			philo->info->t_eat++; // when it reaches the number of philosofers the program ends
		usleep(philo->info->time_eat * 1000); //takes microseconds
		philo->last_meal = return_time(); //save the last time current philosofer ate
		//unlock the forks resources
		pthread_mutex_unlock(&philo->mutex[philo->id - 1]);
		pthread_mutex_unlock(&philo->mutex[philo->id % philo->info->num_philo]);
		//Sleep first, then eat
		ft_print(philo, return_time(philo), "is sleeping");
		usleep(philo->info->time_sleep * 1000);
		ft_print(philo, return_time(philo), "is thinking");
	}
	return (0);
}

int	main(int ac, char **av)
{
	int			i;
	t_args		*arg;
	t_philo		*philo;
	pthread_t	*thread;
	int			err;

	if (ac < 5 || ac > 6)
		return (throw_error());
	arg = (t_args *)malloc(sizeof(t_args));
	if (ft_init_args(arg, av))
		return (ft_free_struc(0, 0, arg));
	philo = malloc(sizeof(t_philo) * arg->num_philo);
	if (init_philo(arg, philo))
		return (1);
	thread = malloc(sizeof(pthread_t) * arg->num_philo);
	i = -1;
	while (++i < philo->info->num_philo)
	{
		err = pthread_create(&thread[i], NULL, doSomething, philo + i);
		if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
		usleep(100);
	}
	func(philo, arg);
	free(thread);
	return (0);
}
