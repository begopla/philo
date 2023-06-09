NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=address
SRC =	main.c \
		actions.c \
		thread.c \
		utils.c \

VPATH = src

OBJDIR = .bin

all: $(NAME)

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))


$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $^ -o $@

$(OBJDIR):
	mkdir .bin

$(NAME): $(OBJ) include/philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

r: re
	printf "\e[1;1H\e[2J";
	./philo 5 800 200 200

clean:
	rm -rf $(OBJDIR)

fclean:
	make clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	clean fclean re nice
