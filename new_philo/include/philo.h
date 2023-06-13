#ifndef PHILO_H
# define PHILO_H

/* Includes and types */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	long long		number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_think;
	long long		must_eat;
	int				end;
	long long		start_ms;
	int				hungry_philosophers;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
}					t_data;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	int				holder;
}					t_fork;

typedef struct s_philo
{
	t_data	*data;
	struct s_philo	*next;
	struct s_philo	*prev;
	int				id;
	int				meals;
	long long		last_eat;
	pthread_mutex_t	last_eat_mutex;
	t_fork			left_fork;
	t_fork			right_fork;
}					t_philo;

/* Colors */

# define RED "\033[31m"
# define NC "\033[0m"

/* Numbers attached to states */

# define L_FORK 0
# define R_FORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5
# define DIED_EXTERN 6

/* Error messages */

# define ERRNBR		4815162342

# define ERRARGS	"\
Usage:  number_of_philosophers time_to_die \
time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

# define ERRTYPE	"Error: Wrong argument type or \
could not allocate.\n"


int				init_time(t_data *data);
long long		get_time(void);
void			ft_sleep(unsigned long long sleep, t_data *data);
long long		get_num(const char *str);

/* Philosophers functions */

int				print_state(t_data *data, t_philo *philo, \
				int state);

t_data			*define_data(char **av, int ac);

t_philo			*generate_philos(t_data *data, int nb);

void			free_philos(t_philo *first, int initialized);

pthread_t		*allocate_threads(int number_of_philosophers);

void			restitute_forks(t_philo *philo);

int				deep_thought(t_data *data, t_philo *philo);

int				take_forks(t_data *data, t_philo *philo);

int				just_eat(t_data *data, t_philo *philo);

int				night_time(t_data *data, t_philo *philo);

void			*routine(void *arg);

void			*lonely_routine(void *arg);

void			free_data(t_data *data);

void			check_death(t_data *data, t_philo *philo);

int				create_threads(t_data *data, t_philo *philo, \
				pthread_t *threads);

int				join_threads(t_data *data, pthread_t *threads);



#endif
