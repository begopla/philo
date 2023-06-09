#include "../include/philo.h"

useconds_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	someone_died(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&(philo->d->death_mutex));
	state = philo->d->died;
	pthread_mutex_unlock(&(philo->d->death_mutex));
	return (state);
}

int	ft_nonum(int n, char **str)
{
	int		i;
	int		j;

	j = 1;
	while (n > 1)
	{
		i = 0;
		while (str[j][i])
		{
			if ((str[j][i] >= '0' && str[j][i] <= '9'))
				i++;
			else
				return (1);
		}
		j++;
		n--;
	}
	return (0);
}


long long	get_num(char *str)
{
	int				i;
	int				sign;
	long unsigned	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = (number * 10) + str[i] - 48;
		i++;
	}
	return (number * sign);
}

int	free_and_exit(t_data *d, t_philo *philo, t_fork *forks)
{
	if (d)
	{
		if (pthread_mutex_destroy(&d->philo_mutex))
			return (1);
		if (pthread_mutex_destroy(&d->death_mutex))
			return (1);
		if (pthread_mutex_destroy(&d->print_mutex))
			return (1);
	}
	if (philo)
		free(philo);
	if (forks)
	{
		if (pthread_mutex_destroy(&forks->fork_mutex))
			return (1);
		free(forks);
	}
	return (0);
}

int	printf_error(char *msg, t_data *d, t_philo *philo, t_fork *forks)
{
	printf("\033[1;31mError: %s\033[0;39m\n",msg);
	free_and_exit(d, philo, forks);
	return (1);
}
