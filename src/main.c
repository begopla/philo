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
		philo->eat_count = 0;
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

static int	mutex_init(t_data *g, t_args a)
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
	a->num_philo = get_num(argv[1]);
	a->die_time = get_num(argv[2]) * 1000;
	a->eat_time = get_num(argv[3]) * 1000;
	a->sleep_time = get_num(argv[4]) * 1000;
	a->repeat_count = -2;
	if (argc == 6)
		a->repeat_count = get_num(argv[5]);
	if (a->num_philo == -1 || a->die_time == -1 || a->eat_time \
		== -1 || a->sleep_time == -1 || a->repeat_count == -1)
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
		return (printf_error("Wrong number of args\n", NULL, NULL, NULL));
	if (ft_nonum(argc, argv))
			return (printf_error("Wrong type of args, only numbers allowed\n", NULL, NULL, NULL));
	if (!args_init(&a, argc, argv))
		return (printf_error("Invalid input\n", &d, NULL, NULL));
	if (!mutex_init(&d, a))
		return (printf_error("Mutex init failure\n", &d, NULL, NULL));
	if (!philo_init(&d, &philos, &forks))
		return (printf_error("Malloc failure\n", &d, philos, forks));
	if (!ft_create_thread(&d, &philos))
		return (printf_error("There were error in threads\n", &d, philos, forks));
	return (free_and_exit(&d, philos, forks));
}
