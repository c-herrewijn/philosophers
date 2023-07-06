NAME = philo
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
IFLAGS = -I$(LIBFT_DIR)
LFLAGS = -L$(LIBFT_DIR) -lft

SRCS =	main.c validations.c cutlery.c philosophers.c threads_create.c \
		threads_launch.c utils.c eat_sleep_think.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
LIBFT_DIR = ../libft
LIBFTNAME = libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME)
	$(CC) $(CFLAGS) $(IFLAGS) $^ -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

$(LIBFT_DIR)/$(LIBFTNAME):
	$(MAKE) -C $(LIBFT_DIR) bonus

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
