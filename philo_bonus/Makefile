NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror -O3 -flto
SRCS =	main.c eat.c parsing.c philo_life.c philosophers.c process_launch.c \
		semaphores.c sleep_think.c time_utils.c utils.c killswitch.c \
		priority.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
