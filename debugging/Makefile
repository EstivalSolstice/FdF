NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = minilbx_opengl_20191021
LIBFT_DIR = libft

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = fdf_debugging.c ../main.c ../draw.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -I.
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX) $(LIBFT) $(FRAMEWORKS) -o $(NAME)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c fdf.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
