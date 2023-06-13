#include "../include/philo.h"

int	_check_last_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(philo->last_eat_mutex));
	if (get_time() - philo->last_eat >= data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		print_state(data, philo, DIED);
		return (0);
	}
	pthread_mutex_unlock(&(philo->last_eat_mutex));
	return (1);
}

void	check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&(data->end_mutex));
			if (data->end)
			{
				pthread_mutex_unlock(&(data->end_mutex));
				return ;
			}
			else
				pthread_mutex_unlock(&(data->end_mutex));
			if (!_check_last_eat(data, philo))
				return ;
			i++;
		}
		usleep(1);
	}
}
