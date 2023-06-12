#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define UP			1
# define DOWN		0

# define LEFT_FORK	-2
# define RIGHT_FORK	2

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_args
{
	int				num_philo;
	time_t			die_time;
	time_t			eat_time;
	time_t			sleep_time;
	long				repeat_count;
}	t_args;

typedef struct t_data
{
	t_args			a;
	int				died;
	useconds_t		init_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	philo_mutex;
}	t_data;

typedef struct s_philo
{
	t_data			*d;
	unsigned char	id;
	pthread_t		t_philosopher;
	int				eat_count;
	time_t			last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	int			right_fork_state;
	int			left_fork_state;
}	t_philo;

int			printf_error(char *msg, t_data *d, t_philo *philo, t_fork *forks);
int			free_and_exit(t_data *d, t_philo *philo, t_fork *forks);
int			someone_died(t_philo *philo);
useconds_t	get_time(void);
int			ft_create_thread(t_data *d, t_philo **philos);
long long	get_num(char *str);
int			ft_nonum(int n, char **str);
void		print_state(t_philo *philo, char *str);
void		eat_action(t_philo *philo);
void		dead_action(t_philo *philo, t_data *d);
void		put_fork(char which_fork, t_philo *philo);
#endif
