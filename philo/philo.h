/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:03:13 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/18 12:04:02 by bpla-rub         ###   ########.fr       */
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

struct s_args;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		last_meal;
	pthread_t		thread_id;
	struct s_args	*args;
}	t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				died;
	int				all_eat;
	long long		first_timestamp;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	writing;
	unsigned long	time;
	t_philo			philosophers[200];
}	t_args;


/*
** ----- error_starter.c -----
*/

int						throw_error(int error);
void					exit_launcher(t_args *args, t_philo *philos);
void					smart_sleep(long long time, t_args *args);
/*
** ----- runner.c -----
*/
int						launcher(t_args *args);
/*
** ----- init.c -----
*/
int						ft_init_all(t_args *args, char **av);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
unsigned long			init_time(void);
long long				time_diff(long long past, long long pres);
void					action_print(t_args *args, int id, char *string);
#endif
