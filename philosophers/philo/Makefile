NAME	=	philo
SRC		=	main.c helpers.c parsing.c initialize.c actions.c routine_monitor.c

HD		= 	philo.h
OBJ		=	$(SRC:%.c=%.o)
CC		=	cc -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

%.o: %.c HD
		$(CC) $(CPPFLAGS) -Wall -Wextra -Werror -pthread -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
