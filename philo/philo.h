/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:03:13 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/29 17:07:32 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft_tools.h"
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

//# define PHILO_EAT "\033[1;95mis eating\033[0;39m"
# define PHILO_EAT "\033[1;32mis eating\033[0;39m"
# define PHILO_SLEEP "\033[1;97mis sleeping\033[0;39m"
# define PHILO_THINK "\033[1;95mis thinking\033[0;39m"
# define PHILO_TAKE_FORK "\033[1;96mhas taken a fork\033[0;39m"
# define PHILO_DIE "\033[1;91mdied\033[0;39m"

/* Enum to handle errors in philosophers */
typedef enum e_philo_err
{
	END = 1,
	INV_ARGS = -1,
	TOO_MANY_PHILO = -2,
	INV_NUM_PHILO = -3,
	INV_DIE_TIME = -4,
	INV_EAT_TIME = -5,
	INV_SLEEP_TIME = -6,
	INV_REPEAT_COUNT = -7,
	NO_MEMORY = -8,
	THREAD_FAILED = -9
}			t_philo_err;

/* Struct to store all data */
typedef struct s_philo_data
{
	int				num_philo;
	useconds_t		init_time;
	long			repeat_count;
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long			eat_count;
	pthread_mutex_t	eat_count_lock;
	int				died;
	pthread_mutex_t	died_lock;
}					t_data;

/* Struct to handle info for every philosopher */
typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	pthread_mutex_t		fork_lock;
	useconds_t			last_meal;
	pthread_mutex_t		last_meal_lock;
	struct s_philo_data	*data;
}						t_philo;

int			print_error(char *param, t_philo_err err_code);

/* Prints error message and exits freeing everything */
void		*free_and_exit(t_list *philos, char *param, t_philo_err err_code);

/* Personal & more precise implementation of the usleep function */
int			ft_usleep(useconds_t usec);

/* Returns current time in miliseconds */
useconds_t	get_time(void);

/* Fills an array with the default info for every philosopher */
t_list		*philo_lst(t_data *d);

/* Creates threads for every philosopher */
void		*philo_init(int num_philo, t_list *philos);

/* Prints current state of a philosopher if applicable */
void		philo_timestamp(t_list *philos, char *action, useconds_t t);
#endif
