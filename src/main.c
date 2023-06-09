#include "../include/philo.h"

static int	philo_init(t_data *d, t_philo **philos, t_fork **forks)
{
	t_philo	*philo;
	int		i;

	*philos = (t_philo *)malloc(sizeof(t_philo) * d->a.num_philo);
	*forks = (t_fork *)malloc(sizeof(t_fork) * d->a.num_philo);
	if (!philos || !forks)
		return (0);
	i = -1;
	while (++i < d->a.num_philo)
	{
		philo = &(*philos)[i];
		philo->d = d;
		philo->id = i + 1;
		philo->d->init_time = get_time();
		philo->last_meal = get_time();
		philo->loop = 0;
		philo->right_fork = &((*forks)[i]);
		philo->left_fork = &((*forks)[i + 1]);
		if (philo->id == d->a.num_philo)
			philo->left_fork = &((*forks)[0]);
		philo->right_fork_state = DOWN;
		philo->left_fork_state = DOWN;
		pthread_mutex_init(&(philo->left_fork->fork_mutex), NULL);
	}
	return (1);
}

static int	global_init(t_data *g, t_args a)
{
	g->a = a;
	g->died = 0;
	if (pthread_mutex_init(&(g->philo_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(g->death_mutex), NULL))
		return (0);
	if (pthread_mutex_init(&(g->print_mutex), NULL))
		return (0);
	return (1);
}

static int	args_init(t_args *a, int argc, char **argv)
{
	a->num_philo = get_input_value(argv[1]);
	a->time_to_die = get_input_value(argv[2]) * 1000;
	a->time_to_eat = get_input_value(argv[3]) * 1000;
	a->time_to_sleep = get_input_value(argv[4]) * 1000;
	a->repeat_count = -2;
	if (argc == 6)
		a->repeat_count = get_input_value(argv[5]);
	if (a->num_philo == -1 || a->time_to_die == -1 || a->time_to_eat \
		== -1 || a->time_to_sleep == -1 || a->repeat_count == -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_args		a;
	t_data		d;
	t_philo		*philos;
	t_fork		*forks;

	if (argc < 5 || argc > 6)
		return (error_handler("Wrong number of args\n", NULL, NULL, NULL));
	if (!args_init(&a, argc, argv))
		return (error_handler("Invalid input\n", &d, NULL, NULL));
	if (!global_init(&d, a))
		return (error_handler("Mutex init failure\n", &d, NULL, NULL));
	if (!philo_init(&d, &philos, &forks))
		return (error_handler("Malloc failure\n", &d, philos, forks));
	if (!thread_handler(&d, &philos))
		return (error_handler("Some errors with threads\n", &d, philos, forks));
	return (clean_exit(&d, philos, forks));
}
