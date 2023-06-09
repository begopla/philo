
#include "../include/philo.h"

static void	ft_philos_init(t_data *data, t_philo *first)
{
	t_philo	*philo;
	size_t	i;

	i = 0;
	philo = first;
	while (philo && ++i)
	{
		philo->data = data;
		philo->id = i;
		philo->meals = 0;
		philo->left_fork.holder = 0;
		philo->right_fork.holder = 0;
		pthread_mutex_init(philo->left_fork.mutex, NULL);
		pthread_mutex_init(&(philo->last_eat_mutex), NULL);
		philo = philo->next;
		if (philo == first)
			break ;
	}
	while (philo)
	{
		philo->right_fork.mutex = philo->next->left_fork.mutex;
		philo = philo->next;
		if (philo == first)
			break ;
	}
}

static void	ft_make_ends_meet(t_philo *philo, t_philo *first)
{
	philo->next = first;
	first->prev = philo;
}

t_philo	*generate_philos(t_data *data, int nb)
{
	t_philo	*philo;
	t_philo	*first;
	int		i;


    first = malloc(sizeof(t_philo));
    if (!first) {
        printf("%s", ERRTYPE); // Print the error message using printf
        return NULL;
    }
    philo = first;
    i = 0;
    while (1)
	{
		philo->next = NULL;
		philo->left_fork.mutex = malloc(sizeof(pthread_mutex_t));
		if (!(philo->left_fork.mutex)) {
			printf("%s", ERRTYPE);
			free_philos(first, 0);
			return NULL;
		}
		if (++i >= nb)
			break;
		philo->next = malloc(sizeof(t_philo));
		if (!(philo->next))
		{
			printf("%s", ERRTYPE);
			free_philos(first, 0);
			return NULL;
		}
		philo->next->prev = philo;
		philo = philo->next;
	}
	ft_make_ends_meet(philo, first);
	ft_philos_init(data, first);
	return first;
}

void	free_philos(t_philo *first, int initialized)
{
	t_philo	*philo;
	t_philo	*tmp;

	philo = first;
	while (philo)
	{
		if (initialized)
			pthread_mutex_destroy(&(philo->last_eat_mutex));
		if (philo->left_fork.mutex)
		{
			if (initialized)
				pthread_mutex_destroy(philo->left_fork.mutex);
			free(philo->left_fork.mutex);
		}
		tmp = philo;
		philo = philo->next;
		free(tmp);
		if (philo == first)
			break ;
	}
}
