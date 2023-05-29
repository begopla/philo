/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:08:28 by bpla-rub          #+#    #+#             */
/*   Updated: 2023/05/29 15:39:38 by bpla-rub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TOOLS_H
# define LIBFT_TOOLS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void		ft_lstadd_back(t_list **lst, t_list *newnode);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
long long	ft_atoi(const char *nptr);
#endif
