#include "../include/philo.h"

static void	take_fork(char which_fork, t_philo *philo)
{
	int		*fork_state;
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
	if (*fork_state == DOWN)
	{
		pthread_mutex_lock(&(fork->fork_mutex));
		*fork_state = UP;
		print_state(philo, "\033[1;96mhas taken a fork\033[0;39m\n");
	}
}

static void	*do_actions(void *arg)
{
	t_philo	*philo;
	int usleep_time;

	philo = (t_philo *)arg;
	usleep(!(philo->id % 2) * 1000);
	while (!someone_died(philo) && philo->eat_count != philo->d->a.repeat_count)
	{
		take_fork(RIGHT_FORK, philo);
		if (philo->right_fork_state == UP && philo->d->a.num_philo > 1)
			take_fork(LEFT_FORK, philo);
		if (philo->right_fork_state == UP && philo->left_fork_state == UP)
		{
			eat_action(philo);
			put_fork(RIGHT_FORK, philo);
			put_fork(LEFT_FORK, philo);
			print_state(philo,"\033[1;97mis sleeping\033[0;39m\n");
			usleep(philo->d->a.sleep_time);
			print_state(philo, "\033[1;95mis thinking\033[0;39m\n");
		}
	}
	return (NULL);
}

static void	*monitor_actions_die(t_data *d, t_philo **philos)
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
			dead_action(&((*philos)[i]), d);
			return (NULL);
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
			do_actions, &((*philos)[i])))
			return (0);
	}
	monitor_actions_die(d, philos);
	i = -1;
	while (++i < d->a.num_philo)
	{
		if (pthread_join((*philos)[i].t_philosopher, NULL))
			return (0);
	}
	return (1);
}
