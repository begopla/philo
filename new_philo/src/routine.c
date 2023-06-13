#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	while (get_time() < data->start_ms)
		usleep(philo->id);
	if (philo->id % 2 == 0)
		usleep(200);
		//ft_sleep(data->time_to_eat * 0.75, data);
	while (1)
	{
		if (!take_forks(data, philo))
			return (restitute_forks(philo), NULL);
		if (!just_eat(data, philo))
			return (restitute_forks(philo), NULL);
		restitute_forks(philo);
		if (!night_time(data, philo))
			return (NULL);
		if (!deep_thought(data, philo))
			return (NULL);
	}
}

void	*lonely_routine(void *arg)
{
	t_philo			*philo;
	t_data	*data;

	philo = arg;
	data = philo->data;
	while (get_time() < data->start_ms)
		usleep(philo->id);
	pthread_mutex_lock(philo->left_fork.mutex);
	philo->left_fork.holder = 1;
	if (!print_state(data, philo, L_FORK))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->end)
			break ;
		pthread_mutex_unlock(&(data->end_mutex));
		usleep(250);
	}
	pthread_mutex_unlock(&(data->end_mutex));
	pthread_mutex_unlock(philo->left_fork.mutex);
	return (NULL);
}
