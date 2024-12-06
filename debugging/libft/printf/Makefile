# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# The name of the output library
NAME = libftprintf.a

# Source files list
SRC =	ft_printf.c \
		ft_check_inputprintf.c \
		ft_handle_specifier.c \
		ft_handle_input_c.c \
		ft_handle_input_d_i.c \
		ft_handle_input_p.c \
		ft_handle_input_s.c \
		ft_handle_input_u.c \
		ft_handle_input_x.c \
		ft_handle_input_xu.c \
		ft_write_return_val.c \
		ft_pf_itoa.c ft_pf_strlen.c

# Automatically generate object files list by replacing .c with .o
OBJ = $(SRC:.c=.o)

# Header file
HEADER = printf.h

# Default target: builds the library
all: $(NAME)

# Rule for building the library from object files
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

# Rule for compiling .c files into .o files
%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< to $@."

# Clean up object files
clean:
	@rm -f $(OBJ)
	@echo "Cleaned up object files."

# Clean up object files and the library
fclean: clean
	@rm -f $(NAME)
	@echo "Removed $(NAME)."

# Rebuild everything from scratch
re: fclean all

# Mark these targets as "phony" so they don't conflict with files named "all", "clean", etc.
.PHONY: all clean fclean re
