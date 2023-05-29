# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpla-rub <bpla-rub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 16:30:41 by bpla-rub          #+#    #+#              #
#    Updated: 2023/05/29 15:40:21 by bpla-rub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 =	philos

SRCS = philo/main.c    \
       philo/time.c    \
       philo/utils.c   \
       philo/init.c    \
	   philo/libft/libft.c   \


OBJS		=	$(SRCS:.c=.o)
HD			=	philo/philo.h
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -pthread
RM			=	rm -rf

all:		$(NAME)

$(NAME):	$(SRCS) $(OBJS) $(HD)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

leaks:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=./readline.supp ./philo \
	

clean:		
			$(RM) philo/*.o
			$(RM) philo/libft/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all 

			
.PHONY:		all clean fclean re
