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

int	get_input_value(char *s)
{
	int	n;

	n = -1;
	while (*s == 32)
		s++;
	if (*s == 45 || (*s != 43 && (*s < 48 || *s > 57)))
		return (n);
	if (*s == 43)
		s++;
	while (*s >= 48 && *s <= 57)
	{
		if (n == -1)
			n = 0;
		n = n * 10 + *s - 48;
		s++;
	}
	return (n);
}

int	clean_exit(t_data *d, t_philo *philo, t_fork *forks)
{
	if (d)
	{
		if (pthread_mutex_destroy(&d->death_mutex))
			return (EXIT_FAILURE);
		if (pthread_mutex_destroy(&d->philo_mutex))
			return (EXIT_FAILURE);
	}
	if (philo)
		free(philo);
	if (forks)
	{
		if (pthread_mutex_destroy(&forks->fork_mutex))
			return (EXIT_FAILURE);
		free(forks);
	}
	return (EXIT_SUCCESS);
}

int	error_handler(char *msg, t_data *d, t_philo *philo, t_fork *forks)
{
	write(2, RED_BOLD, 7);
	while (*msg)
		write(2, &*msg++, 1);
	write(2, RESET, 4);
	clean_exit(d, philo, forks);
	return (EXIT_FAILURE);
}
