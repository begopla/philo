#include "../include/philo.h"

int	init_time(t_data *data)
{
	struct timeval	tv;

	if (!data || gettimeofday(&tv, NULL) != 0)
		return (0);
	data->start_ms = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) \
							+ 1 + data->number_of_philosophers / 10);
	return (1);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(unsigned long long sleep, t_data *data)
{
	long long	awake;

	awake = get_time() + sleep;
	while (get_time() < awake)
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->end)
		{
			pthread_mutex_unlock(&(data->end_mutex));
			break ;
		}
		else
			pthread_mutex_unlock(&(data->end_mutex));
		usleep(500);
	}
}
