#include "../include/philo.h"

static long long	ft_numspec(const char *str, int i, long long nbr, long long sign)
{
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		if ((nbr * sign) > 2147483647 || (nbr * sign) < -2147483648)
			return (ERRNBR);
		i++;
	}
	if (str[i])
		return (ERRNBR);
	return (nbr * sign);
}

long long	get_num(const char *str)
{
	long long		nbr;
	long long		sign;
	size_t			i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	return (ft_numspec(str, i, nbr, sign));
}

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
