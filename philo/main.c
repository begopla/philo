/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:46:07 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/29 17:07:30 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	parse_args(char **av)
{
	t_data	d;

	d.num_philo = ft_atoi(av[1]);
	if (d.num_philo <= 0)
		free_and_exit(NULL, av[1], INV_NUM_PHILO);
	if (d.num_philo > 200)
		free_and_exit(NULL, av[1], TOO_MANY_PHILO);
	d.die_time = ft_atoi(av[2]);
	if (d.die_time == -1)
		free_and_exit(NULL, av[2], INV_DIE_TIME);
	d.eat_time = ft_atoi(av[3]);
	if (d.eat_time == -1)
		free_and_exit(NULL, av[3], INV_EAT_TIME);
	d.sleep_time = ft_atoi(av[4]);
	if (d.sleep_time == -1)
		free_and_exit(NULL, av[4], INV_SLEEP_TIME);
	d.repeat_count = -2;
	if (av[5])
	{
		d.repeat_count = ft_atoi(av[5]);
		if (d.repeat_count == -1 || !d.repeat_count)
			free_and_exit(NULL, av[5], INV_REPEAT_COUNT);
	}
	return (d);
}

int	main(int ac, char **av)
{
	t_data	d;
	t_list	*philos;

	if (ac != 5 && ac != 6)
	{
		free_and_exit(NULL, NULL, INV_ARGS);
		printf("\nusage: philo <num_philo> <die_time>");
		printf(" <eat_time> <sleep_time> [<repeat_times>]\n");
		return (1);
	}
	d = parse_args(av);
	if (d.num_philo <= 0 || d.num_philo > 200 || d.die_time == -1 || \
		d.eat_time == -1 || d.sleep_time == -1 || d.repeat_count == -1 || \
		!d.repeat_count)
		return (1);
	d.init_time = get_time();
	d.died = 0;
	d.eat_count = 0;
	pthread_mutex_init(&d.died_lock, NULL);
	pthread_mutex_init(&d.eat_count_lock, NULL);
	philos = philo_lst(&d);
	ft_lstlast(philos)->next = philos;
	philo_init(d.num_philo, philos);
	free_and_exit(philos, NULL, END);
	return (0);
}
