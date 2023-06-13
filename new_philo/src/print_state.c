
#include "../include/philo.h"

static void	ft_print(long long time, int id, int state)
{
	const char	*print_state;

	if (state == L_FORK || state == R_FORK)
		print_state = "\033[1;96mhas taken a fork\033[0;39m";
	if (state == EATING)
		print_state = "\033[1;32mis eating\033[0;39m";
	if (state == SLEEPING)
		print_state = "\033[1;97mis sleeping\033[0;39m";
	if (state == THINKING)
		print_state = "\033[1;95mis thinking\033[0;39m";
	if (state == DIED)
		print_state = "\033[1;91mdied\033[0;39m 💀";
	printf("%-4lld %-1d %s\n", \
	time, id, print_state);
}

static int	_check_end(t_data *data, t_philo *philo, int state)
{
	pthread_mutex_lock(&(data->end_mutex));
	if (data->end)
	{
		pthread_mutex_unlock(&(data->end_mutex));
		if (state != DIED)
			restitute_forks(philo);
		return (pthread_mutex_unlock(&(data->print_mutex)), 0);
	}
	pthread_mutex_unlock(&(data->end_mutex));
	pthread_mutex_lock(&(data->eat_mutex));
	if (!data->hungry_philosophers && state != EATING)
	{
		pthread_mutex_unlock(&(data->eat_mutex));
		pthread_mutex_lock(&(data->end_mutex));
		data->end = 1;
		pthread_mutex_unlock(&(data->end_mutex));
		return (pthread_mutex_unlock(&(data->print_mutex)), 0);
	}
	pthread_mutex_unlock(&(data->eat_mutex));
	return (1);
}

static void	ft_print_death(t_data *data, t_philo *philo, \
			long long time_elapsed_ms)
{
	pthread_mutex_lock(&(data->end_mutex));
	data->end = 1;
	pthread_mutex_unlock(&(data->end_mutex));
	ft_print(time_elapsed_ms, philo->id, DIED);
	pthread_mutex_unlock(&(data->print_mutex));
}

int	print_state(t_data *data, t_philo *philo, int state)
{
	long long		current;
	long long		time;

	pthread_mutex_lock(&(data->print_mutex));
	if (!_check_end(data, philo, state))
		return (0);
	current = get_time();
	time = current - data->start_ms;
	if (state == DIED)
		return (ft_print_death(data, philo, time), 0);
	pthread_mutex_lock(&(philo->last_eat_mutex));
	if (current - philo->last_eat > data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		restitute_forks(philo);
		pthread_mutex_unlock(&(data->print_mutex));
		return (print_state(data, philo, DIED));
	}
	else
	{
		pthread_mutex_unlock(&(philo->last_eat_mutex));
		ft_print(time, philo->id, state);
		pthread_mutex_unlock(&(data->print_mutex));
		return (1);
	}
	return (0);
}
