#include "../include/philo.h"

static void	take_fork(char which_fork, t_philo *philo)
{
	bool	*fork_state;
	t_fork	*fork;

	if (which_fork == LEFT_FORK)
	{
		fork_state = &(philo->left_fork_state);
		fork = philo->left_fork;
	}
	else if (which_fork == RIGHT_FORK)
	{
		fork_state = &(philo->right_fork_state);
		fork = philo->right_fork;
	}
	if (someone_died(philo))
		return ;
	if (*fork_state == DOWN)
	{
		pthread_mutex_lock(&(fork->fork_mutex));
		*fork_state = UP;
		pthread_mutex_lock(&(philo->g->print_mutex));
		if (!someone_died(philo))
			printf("%u %d has taken a fork 🍴\n", get_time() - philo->g->init_time, philo->id);
		pthread_mutex_unlock(&(philo->g->print_mutex));
	}
}

static void	put_fork(char which_fork, t_philo *philo)
{
	bool	*fork_state;
	t_fork	*fork;

	if (which_fork == LEFT_FORK)
	{
		fork_state = &(philo->right_fork_state);
		fork = philo->right_fork;
	}
	else if (which_fork == RIGHT_FORK)
	{
		fork_state = &(philo->left_fork_state);
		fork = philo->left_fork;
	}
	*fork_state = DOWN;
	pthread_mutex_unlock(&(fork->fork_mutex));
}

static void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(65000);
	while (!someone_died(philo) && philo->loop != philo->g->a.repeat_count)
	{
		take_fork(LEFT_FORK, philo);
		if (philo->left_fork_state == UP && philo->g->a.num_philo > 1)
			take_fork(RIGHT_FORK, philo);
		if (philo->left_fork_state == UP && philo->right_fork_state == UP)
		{
			state_handler(EAT, philo, NULL);
			put_fork(RIGHT_FORK, philo);
			put_fork(LEFT_FORK, philo);
			state_handler(SLEEP, philo, NULL);
			state_handler(THINK, philo, NULL);
		}
	}
	if (philo->right_fork_state == UP)
		pthread_mutex_unlock(&(philo->right_fork->fork_mutex));
	if (philo->left_fork_state == UP)
		pthread_mutex_unlock(&(philo->left_fork->fork_mutex));
	return (NULL);
}

static void	*supervisor_routine(void *arg)
{
	t_data	*g;
	t_philo		**philos;
	int			i;

	philos = (t_philo **)arg;
	g = (*philos)->g;
	i = -1;
	while (1)
	{
		if (++i == g->a.num_philo)
			i = 0;
		pthread_mutex_lock(&(g->philo_mutex));
		if ((*philos)[i].loop == g->a.repeat_count)
		{
			pthread_mutex_unlock(&(g->philo_mutex));
			return (NULL);
		}
		if (get_time() - (*philos)[i].last_meal > g->a.time_to_die / 1000)
		{
			pthread_mutex_unlock(&(g->philo_mutex));
			return (state_handler(DEAD, &((*philos)[i]), g));
		}
		pthread_mutex_unlock(&(g->philo_mutex));
	}
	return (NULL);
}

// static void	*supervisor_routine(t_data *d, t_philo **philos)
// {
// 	int			i;

// 	i = -1;
// 	while (1)
// 	{
// 		if (++i == d->a.num_philo)
// 			i = 0;
// 		pthread_mutex_lock(&(d->philo_mutex));
// 		if ((*philos)[i].loop == d->a.repeat_count)
// 		{
// 			pthread_mutex_unlock(&(d->philo_mutex));
// 			return (NULL);
// 		}
// 		if (get_time() - (*philos)[i].last_meal > d->a.time_to_die / 1000)
// 		{
// 			pthread_mutex_unlock(&(d->philo_mutex));
// 			return (state_handler(DEAD, &((*philos)[i]), d));
// 		}
// 		pthread_mutex_unlock(&(d->philo_mutex));
// 	}
// 	return (NULL);
// }

bool	thread_handler(t_data *d, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < d->a.num_philo)
	{
		if (pthread_create(&((*philos)[i].t_philosopher), NULL, \
			philosopher_routine, &((*philos)[i])))
			return (false);
	}
	if (pthread_create(&(d->t_supervisor), NULL, supervisor_routine, philos))
		return (false);
	while (i--)
	{
		if (pthread_join((*philos)[i].t_philosopher, NULL))
			return (false);
	}
	if (pthread_join(d->t_supervisor, NULL))
		return (false);
	return (true);
}
