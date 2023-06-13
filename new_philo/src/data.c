
#include "../include/philo.h"

static int	ft_check_data(t_data *data, int size)
{
	if (data->number_of_philosophers == ERRNBR \
	|| data->time_to_die == ERRNBR \
	|| data->time_to_eat == ERRNBR \
	|| data->time_to_sleep == ERRNBR \
	|| data->must_eat == ERRNBR)
		return (0);
	else if (data->number_of_philosophers < 1 \
	|| data->time_to_die < 0 \
	|| data->time_to_eat < 0 \
	|| data->time_to_sleep < 0 \
	|| (data->must_eat < 0 && size == 6))
		return (0);
	return (1);
}

static int	_check_mutexes(t_data *data)
{
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
	{
		printf("%s", ERRTYPE);
		free(data);
		return (0);
	}
	else if (pthread_mutex_init(&(data->eat_mutex), NULL) != 0)
	{
		printf("%s", ERRTYPE);
		pthread_mutex_destroy(&(data->print_mutex));
		free(data);
		return (0);
	}
	else if (pthread_mutex_init(&(data->end_mutex), NULL) != 0)
	{
		printf("%s", ERRTYPE);
		pthread_mutex_destroy(&(data->print_mutex));
		pthread_mutex_destroy(&(data->eat_mutex));
		free(data);
		return (0);
	}
	else
		return (1);
}

t_data	*define_data(char **av, int ac)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("%s", ERRTYPE), NULL);
	data->end = 0;
	data->number_of_philosophers = get_num(av[1]);
	data->time_to_die = get_num(av[2]);
	data->time_to_eat = get_num(av[3]);
	data->time_to_sleep = get_num(av[4]);
	data->hungry_philosophers = data->number_of_philosophers;
	if (ac == 6)
		data->must_eat = get_num(av[5]);
	else
		data->must_eat = -1;
	if (!ft_check_data(data, ac))
		return (free(data),printf("%s", ERRTYPE), NULL);
	if (!_check_mutexes(data))
		return (NULL);
	return (data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->eat_mutex));
	pthread_mutex_destroy(&(data->end_mutex));
	free(data);
}
