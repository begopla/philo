/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:46:07 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/18 12:29:18 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;
	int		error;

	if (ac < 5 || ac > 6)
		return (throw_error(1));
	error = ft_init_all(&args, av);
	if (error)
		return (throw_error(error));
	if (launcher(&args))
		return (printf("there was an error creating the threads\n"));
	return (0);
}
