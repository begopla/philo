#include "../include/philo.h"

void	eat_action(t_philo *philo)
{
	print_state(philo, "\033[1;32mis eating\033[0;39m\n");
	pthread_mutex_lock(&(philo->d->philo_mutex));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->d->philo_mutex));
	usleep(philo->d->a.eat_time);
	pthread_mutex_lock(&(philo->d->philo_mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->d->philo_mutex));
}

void	dead_action(t_philo *philo, t_data *d)
{
	pthread_mutex_lock(&(d->death_mutex));
	d->died = 1;
	pthread_mutex_unlock(&(d->death_mutex));
	pthread_mutex_lock(&((*philo).d->print_mutex));
	printf("%u %d	",get_time()- philo->d->init_time, (*philo).id);
	printf("\033[1;91mdied\033[0;39m 💀\n");
	pthread_mutex_unlock(&((*philo).d->print_mutex));
}

void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->d->print_mutex));
	if (!someone_died(philo))
	{
		printf("%u %d	",get_time()- philo->d->init_time, philo->id);
		printf("%s", str);
	}
	pthread_mutex_unlock(&(philo->d->print_mutex));
}

void	put_fork(char which_fork, t_philo *philo)
{
	int		*fork_state;
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
