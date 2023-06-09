#include "../include/philo.h"

static void	*eat_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->d->print_mutex));
	if (!someone_died(philo))
	{
		printf("%u %d	",get_time()- philo->d->init_time, philo->id);
		printf("\033[1;32mis eating\033[0;39m\n");

	}
	pthread_mutex_unlock(&(philo->d->print_mutex));
	pthread_mutex_lock(&(philo->d->philo_mutex));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->d->philo_mutex));
	usleep(philo->d->a.eat_time);
	pthread_mutex_lock(&(philo->d->philo_mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->d->philo_mutex));
	return (NULL);
}

static void	*sleep_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->d->print_mutex));
	if (!someone_died(philo))
	{
		printf("%u %d	",get_time()- philo->d->init_time, philo->id);
		printf("\033[1;97mis sleeping\033[0;39m\n");
	}
	pthread_mutex_unlock(&(philo->d->print_mutex));
	usleep(philo->d->a.sleep_time);
	return (NULL);
}

static void	*think_state(t_philo *philo)
{
	pthread_mutex_lock(&(philo->d->print_mutex));
	if (!someone_died(philo))
	{
		printf("%u %d	",get_time()- philo->d->init_time, philo->id);
		printf("\033[1;95mis thinking\033[0;39m\n");
	}
	pthread_mutex_unlock(&(philo->d->print_mutex));
	return (NULL);
}

static void	*dead_state(t_philo *philo, t_data *d)
{
	pthread_mutex_lock(&(d->death_mutex));
	d->died = 1;
	pthread_mutex_unlock(&(d->death_mutex));
	pthread_mutex_lock(&((*philo).d->print_mutex));
	printf("%u %d	",get_time()- philo->d->init_time, (*philo).id);
	printf("\033[1;91mdied\033[0;39m 💀\n");
	pthread_mutex_unlock(&((*philo).d->print_mutex));
	return (NULL);
}

void	*state_handler(char state, t_philo *philo, t_data *d)
{
	if (state == EAT)
		return (eat_state(philo));
	else if (state == SLEEP)
		return (sleep_state(philo));
	else if (state == THINK)
		return (think_state(philo));
	else if (state == DEAD)
		return (dead_state(philo, d));
	return (NULL);
}
