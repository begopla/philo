/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:46:07 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/18 12:29:18 by bpla-rub         ###   ########.fr       */
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

void	print(t_philo *philo, unsigned long time, char *is_doing)
{
	pthread_mutex_lock(philo->print);
	printf("%lums	%d %s\n", time, philo->id, is_doing);
	pthread_mutex_unlock(philo->print);
}

void	*doo(void *p)
{
	t_philo	*philo;
	int left_fork;
	int right_fork; 

	philo = (t_philo *)p;
	// if (philo->id % 2 == 0)
	// 	usleep(10);
	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->info->num_philo;
	philo->last_meal = init_time();
	while (1)
	{
		pthread_mutex_lock(&philo->mutex[left_fork]);
		print(philo, return_time(philo), "has taken a fork");
		pthread_mutex_lock(&philo->mutex[right_fork]);
		print(philo, return_time(philo), "has taken a fork");
		print(philo, return_time(philo), "is eating");
		pthread_mutex_lock(philo->m_ate); // Lock t_eat_mutex before accessing t_eat variable
		philo->ate++;
		pthread_mutex_unlock(philo->m_ate);
		//pthread_mutex_lock(philo->info->mt_eat);
		if (philo->ate == philo->info->must_eat)
		{
			philo->info->t_eat++;
		//	pthread_mutex_unlock(philo->info->mt_eat);
		}
		// else
		// 	pthread_mutex_unlock(philo->info->mt_eat);
		usleep(philo->info->time_eat * 1000);
		philo->last_meal = init_time();
		pthread_mutex_unlock(&philo->mutex[left_fork]);
		pthread_mutex_unlock(&philo->mutex[right_fork]);
		print(philo, return_time(philo), "is sleeping");
		usleep(philo->info->time_sleep * 1000);
		print(philo, return_time(philo), "is thinking");
	}
	return (0);
}

void func(t_philo *philo, t_args *var)
{
    int i = 0;

    while (1)
    {
		// pthread_mutex_lock(philo->t_eat); // lock before accessing shared variables
        if (philo[i].info->t_eat == philo[i].info->num_philo)
        {
            destroy_mutex(philo);
            ft_free_struc(philo, philo->mutex, var);
            return;
        }
        unsigned long current_time = init_time();
        unsigned long time_diff = current_time - philo[i].last_meal;
        //printf("Philosopher %d - current_time: %lums, time_diff: %lums, time_die: %dms\n", philo[i].id, current_time, time_diff, var->time_die);
        if (time_diff >= (unsigned long)var->time_die)
        {
            // pthread_mutex_lock(philo[i].print);
            printf("%lums %d died\n", return_time(&philo[i]), philo[i].id);
			// pthread_mutex_unlock(philo[i].print);
            destroy_mutex(philo);
            ft_free_struc(philo, philo->mutex, var);
            return;
        }
        i = (i + 1) % var->num_philo;
        usleep(500);
    }
}

int	main(int ac, char **av)
{
	int			i;
	t_args		*arg;
	t_philo		*philo;
	pthread_t	*thread;

	if (ac < 5 || ac > 6)
		return (throw_error());
	arg = (t_args *)malloc(sizeof(t_args));
	if (ft_init_args(arg, av))
		return (ft_free_struc(0, 0, arg));
	philo = (t_philo *)malloc(sizeof(t_philo) * arg->num_philo);
	if (init_philo(arg, philo))
		return (1);
	thread = malloc(sizeof(pthread_t) * arg->num_philo);
	i = -1;

	while (++i < philo->info->num_philo)
	{
		pthread_create(&thread[i], NULL, doo, philo + i);
		usleep(100);
	}
	func(philo, arg);
	// i = 0;
	// while(i++ < arg->num_philo)
	// 	pthread_join(thread[i], NULL);
	// destroy_mutex(philo);
	free(thread);
	// free(philo);
	// free(arg);
	return (0);
}
