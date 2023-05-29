/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:00:56 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/29 17:07:41 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

useconds_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		before;
	useconds_t		after;

	before = get_time();
	after = before;
	while (after - before < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = get_time();
	}
	return (0);
}
