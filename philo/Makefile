NAME	=	philo
SRC		=	main.c helpers.c parsing.c initialize.c actions.c routine_monitor.c
OBJ		=	$(SRC:%.c=%.o)
CC		=	cc -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c philo.h
		$(CC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
