#include "../include/philo.h"

static void	_set_time_to_think(t_data *data)
{
	data->time_to_think = 0;
	if (data->time_to_eat == 0 && data->time_to_sleep == 0)
		data->time_to_think = 100;
	else if (data->number_of_philosophers % 2 != 0)
		data->time_to_think = ((data->time_to_eat * 2) \
									- data->time_to_sleep) \
									* 1000;
	if (data->time_to_think < 0)
		data->time_to_think = 0;
}

static t_data	*init_data(int ac, char **av, t_philo **philos_ptr, \
	pthread_t **threads_ptr)
{
	t_data			*data;
	t_philo			*philos;
	pthread_t		*threads;

	data = define_data(av, ac);
	if (!data)
		return (NULL);
	if (data->must_eat == 0)
		return (free_data(data), NULL);
	philos = generate_philos(data, data->number_of_philosophers);
	if (!philos)
		return (free_data(data), NULL);
	threads = allocate_threads(data->number_of_philosophers);
	if (!threads)
		return (free_data(data), free_philos(philos, 1), NULL);
	*philos_ptr = philos;
	*threads_ptr = threads;
	_set_time_to_think(data);
	return (data);
}

int	philo(int argc, char **argv)
{
	t_data			*data;
	t_philo			*philos;
	pthread_t		*threads;

	data = init_data(argc, argv, &philos, &threads);
	if (!data)
		return (1);
	init_time(data);
	if (create_threads(data, philos, threads))
		check_death(data, philos);
	else
	{
		pthread_mutex_lock(&(data->end_mutex));
		data->end = 1;
		pthread_mutex_unlock(&(data->end_mutex));
	}
	join_threads(data, threads);
	free_data(data);
	free_philos(philos, 1);
	free(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("%s", ERRARGS);
		return (1);
	}
	else
		return (philo(argc, argv));
}
