/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:03:13 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/09 14:00:48 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_args
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				t_eat;
	unsigned long	time;
}	t_args;

typedef struct s_philo
{
	int				ate;
	int				id;
	t_args			*info;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*print;
	unsigned long	last_meal;
}	t_philo;

int				throw_error(void);
int				ft_init_args(t_args *var, char **av);
unsigned long	init_time(void);
unsigned long	return_time(t_philo *philo);
int				ft_atoi(char *str);
void			destroy_mutex(t_philo *philo);
int				ft_free_struc(t_philo *philo, pthread_mutex_t *m, t_args *var);
int				init_philo(t_args *var, t_philo *philo);
#endif
