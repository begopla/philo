#ifndef PHILO_H
# define PHILO_H

// Libraries ------------------------------------------------------------------>

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

// Macros --------------------------------------------------------------------->

# define THINK		0
# define EAT		1
# define SLEEP		2
# define DEAD		3

# define UP			1
# define DOWN		0

# define LEFT_FORK	-42
# define RIGHT_FORK 42

# define RED_BOLD	"\033[1;31m"
# define RESET		"\x1b[0m"

// Structures ----------------------------------------------------------------->

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_args
{
	int				num_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				repeat_count;
}	t_args;

typedef struct t_data
{
	t_args			a;
	int			died;
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
	int				loop;
	time_t			last_meal;
	t_fork			*right_fork;
	t_fork			*left_fork;
	int			right_fork_state;
	int			left_fork_state;
}	t_philo;

// Functions ------------------------------------------------------------------>

int	thread_handler(t_data *d, t_philo **philos);
void	*state_handler(char state, t_philo *philo, t_data *d);

int		someone_died(t_philo *philo);
useconds_t	get_time(void);
int		get_input_value(char *s);
int		clean_exit(t_data *d, t_philo *philo, t_fork *forks);
int		error_handler(char *msg, t_data *d, t_philo *philo, t_fork *forks);

#endif
