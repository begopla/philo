#include "../include/philo.h"

void	restitute_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->right_fork.holder)
			pthread_mutex_unlock(philo->right_fork.mutex);
		philo->right_fork.holder = 0;
		if (philo->left_fork.holder)
			pthread_mutex_unlock(philo->left_fork.mutex);
		philo->left_fork.holder = 0;
	}
	else
	{
		if (philo->left_fork.holder)
			pthread_mutex_unlock(philo->left_fork.mutex);
		philo->left_fork.holder = 0;
		if (philo->right_fork.holder)
			pthread_mutex_unlock(philo->right_fork.mutex);
		philo->right_fork.holder = 0;
	}
}

int	take_forks(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork.mutex);
		philo->left_fork.holder = 1;
		if (!print_state(data, philo, L_FORK))
			return (0);
		pthread_mutex_lock(philo->right_fork.mutex);
		philo->right_fork.holder = 1;
		if (!print_state(data, philo, R_FORK))
			return (0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork.mutex);
		philo->right_fork.holder = 1;
		if (!print_state(data, philo, R_FORK))
			return (0);
		pthread_mutex_lock(philo->left_fork.mutex);
		philo->left_fork.holder = 1;
		if (!print_state(data, philo, L_FORK))
			return (0);
	}
	return (1);
}

int	just_eat(t_data *data, t_philo *philo)
{
	if (++philo->meals == data->must_eat)
	{
		pthread_mutex_lock(&(data->eat_mutex));
		data->hungry_philosophers -= 1;
		pthread_mutex_unlock(&(data->eat_mutex));
	}
	if (!print_state(data, philo, EATING))
		return (0);
	pthread_mutex_lock(&(philo->last_eat_mutex));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	ft_sleep(data->time_to_eat, data);
	return (1);
}

int	night_time(t_data *data, t_philo *philo)
{
	if (!print_state(data, philo, SLEEPING))
		return (0);
	ft_sleep(data->time_to_sleep, data);
	return (1);
}

int	deep_thought(t_data *data, t_philo *philo)
{
	if (!print_state(data, philo, THINKING))
		return (0);
	// if (data->time_to_think)
	// 	ft_sleep(data->time_to_think/1000, data);
	return (1);
}
