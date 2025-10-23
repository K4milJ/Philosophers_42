NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f

SRC = 	dinner \
		ft_atol \
		input \
		monitoring \
		philo \
		print \
		safe_functions \
		synchronization \
		utils_func \
		utils_sim

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
