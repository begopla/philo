/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:11:10 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/29 17:07:45 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philo_get_data(t_data *d, int i)
{
	t_philo	*node;

	node = malloc(sizeof(struct s_philo));
	if (!node)
		return (free_and_exit(NULL, NULL, THREAD_FAILED));
	node->id = i + 1;
	node->thread_id = 0;
	pthread_mutex_init(&node->fork_lock, NULL);
	pthread_mutex_init(&node->last_meal_lock, NULL);
	node->data = d;
	node->last_meal = 0;
	return (node);
}

t_list	*philo_lst(t_data *d)
{
	int		i;
	t_list	*philos;

	i = -1;
	philos = NULL;
	while (++i < d->num_philo)
		ft_lstadd_back(&philos, ft_lstnew(philo_get_data(d, i)));
	return (philos);
}

int	print_error(char *param, t_philo_err err_code)
{
	printf("philo: ");
	if (err_code == INV_ARGS)
		printf("invalid number of arguments\n");
	if (err_code == NO_MEMORY)
		printf("no memory left on device\n");
	if (err_code == THREAD_FAILED)
		printf("failed to create a thread\n");
	if (err_code == INV_NUM_PHILO)
		printf("invalid philosopher_count: %s\n", param);
	if (err_code == INV_DIE_TIME)
		printf("invalid time_to_die: %s\n", param);
	if (err_code == INV_EAT_TIME)
		printf("invalid time_to_eat: %s\n", param);
	if (err_code == INV_SLEEP_TIME)
		printf("invalid time_to_sleep: %s\n", param);
	if (err_code == INV_REPEAT_COUNT)
		printf("invalid repeat_times: %s\n", param);
	if (err_code == TOO_MANY_PHILO)
		printf("not be able to handle that many philosophers: %s\n", param);
	return (1);
}

void	philo_timestamp(t_list *philos, char *action, useconds_t t)
{
	useconds_t	time;
	t_philo		*philo;
	int			died;
	int			eat_count;

	philo = philos->content;
	pthread_mutex_lock(&philo->data->died_lock);
	died = philo->data->died;
	pthread_mutex_lock(&philo->data->eat_count_lock);
	eat_count = philo->data->eat_count;
	time = get_time() - philo->data->init_time;
	if (philo->data->repeat_count * philo->data->num_philo != \
			eat_count && (!died || action[7] == 'd'))
	{
		printf("\033[1;39m%u\033  \033[1;34m%d  \033[0;39m%s\n", \
			time, philo->id, action);
	}
	if (action[10] == 'e')
		philo->data->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_count_lock);
	pthread_mutex_unlock(&philo->data->died_lock);
	if (philo->data->repeat_count * philo->data->num_philo != \
			eat_count && (!died || action[7] == 'd'))
		ft_usleep(t);
}

void	*free_and_exit(t_list *philos, char *param, t_philo_err err_code)
{
	t_philo	*philo;
	t_list	*temp;

	temp = philos;
	if (err_code != END)
		print_error(param, err_code);
	while (philos)
	{
		philo = philos->content;
		if (philo->id == philo->data->num_philo)
			philos->next = NULL;
		philos = philos->next;
	}
	ft_lstclear(&temp, free);
	return (NULL);
}
