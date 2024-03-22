NAME		= FdF

CC			= gcc
UNAME 		:= $(shell uname -s)

CC_FLAGS	= -Wall -Wextra -Werror -g
INCLUDES	= -Iinclude -Ilibft

SRC_DIR		= src
SRC			= get_next_line.c get_next_line_utils.c main.c ft_io.c ft_render.c ft_utils.c ft_atoi_base.c hooks.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

OUT_DIR		= build
OBJS		= $(addprefix $(OUT_DIR)/, $(SRC:.c=.o))

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_PATH = ./mlx
MLX = $(MLX_PATH)/libmlx.a
INCLUDES += -Imlx

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) bonus

$(MLX):
	make -C $(MLX_PATH)
	cp $(MLX_PATH)/libmlx.a .

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c | $(OUT_DIR) $(LIBFT) $(MLX)
	$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) | $(OUT_DIR) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OUT_DIR)
	
fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -Rf $(NAME)

re: fclean all

.PHONY: clean fclean re all libft
