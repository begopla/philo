#include "../include/philo.h"

static void	take_fork(char which_fork, t_philo *philo)
{
	int	*fork_state;
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
		pthread_mutex_lock(&(philo->d->print_mutex));
		if (!someone_died(philo))
		{
			printf("%u %d	",get_time()- philo->d->init_time, philo->id);
			printf("\033[1;96mhas taken a fork\033[0;39m\n");
		}
		pthread_mutex_unlock(&(philo->d->print_mutex));
	}
}

static void	put_fork(char which_fork, t_philo *philo)
{
	int	*fork_state;
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
		usleep(5000);
	while (!someone_died(philo) && philo->eat_count != philo->d->a.repeat_count)
	{
		take_fork(LEFT_FORK, philo);
		if (philo->left_fork_state == UP && philo->d->a.num_philo > 1)
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

static void	*supervisor_routine(t_data *d, t_philo **philos)
{
	int			i;

	i = -1;
	while (1)
	{
		if (++i == d->a.num_philo)
			i = 0;
		pthread_mutex_lock(&(d->philo_mutex));
		if ((*philos)[i].eat_count == d->a.repeat_count)
		{
			pthread_mutex_unlock(&(d->philo_mutex));
			return (NULL);
		}
		if ((get_time() - (*philos)[i].last_meal) > d->a.die_time / 1000)
		{
			pthread_mutex_unlock(&(d->philo_mutex));
			return (state_handler(DEAD, &((*philos)[i]), d));
		}
		pthread_mutex_unlock(&(d->philo_mutex));
	}
	return (NULL);
}

int	ft_create_thread(t_data *d, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < d->a.num_philo)
	{
		if (pthread_create(&((*philos)[i].t_philosopher), NULL, \
			philosopher_routine, &((*philos)[i])))
			return (0);
	}
	supervisor_routine(d, philos);
	i = -1;
	while (++i < d->a.num_philo)
	{
		if (pthread_join((*philos)[i].t_philosopher, NULL))
			return (0);
	}
	return (1);
}
