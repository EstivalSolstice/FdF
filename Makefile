NAME := fdf
# BONUS_NAME := pipex_bonus
.DEFAULT_GOAL := all
CC := cc
RM := rm -rf

# INCLUDES := -Iminilbx_opengl_20191021

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

# OBJ_DIR := _obj
# INC_DIRS := . libft
# SRC_DIRS := . 
# BONUS_DIR := checker_bonus/_obj_bonus
OBJ_DIR := _obj
# BONUS_DIR := bonus/_obj_bonus
INC_DIRS := . libft
SRC_DIRS := .

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

# # Platform-specific libraries
# ifeq ($(shell uname), Darwin) # macOS
# 	FRAMEWORKS := -framework OpenGL -framework AppKit
# else # Linux
# 	FRAMEWORKS := -lX11 -lXext -lm
# endif

# MiniLibX library path and file
MLX_PATH := minilbx_opengl_20191021
MLX_LIB := $(MLX_PATH)/libmlx.a
MLX_INC := -I$(MLX_PATH)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := main.c camera.c projection.c render.c input.c draw.c map.c parse_utils.c init.c presets.c

# MLX_SRCS := $(wildcard minilbx_opengl_20191021/*.c)

# BONUS_SRCS := 	bonus/main_bonus.c bonus/split_with_quotes_bonus.c \
# 				bonus/exec_command_bonus.c bonus/exec_command_helpers_bonus.c \
# 				bonus/pipex_utils_bonus.c bonus/pipex_bonus.c \
# 				bonus/process_management_bonus.c bonus/file_operations_bonus.c \
# 				bonus/error_exit_bonus.c bonus/parse_command_bonus.c \
# 				bonus/parse_command_helpers_bonus.c bonus/process_family_bonus.c \
# 				bonus/search_and_exec_bonus.c

# BONUS_SRCS := 	cps_convert_args.c cps_helpers.c cps_initialize.c \
# 				cps_main.c cps_operations.c cps_parse_validate.c \
# 				cps_sort_assign_indices.c 

################################################################################
###############                  OBJECT FILES                     ##############
################################################################################

# Common object files used by both main and bonus
COMMON_OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# MLX_OBJS := $(MLX_SRCS:.c=.o)

# Main program object files
# MAIN_OBJS := $(addprefix $(OBJ_DIR)/, $(MAIN_SRCS:%.c=%.o))

# Bonus program object files
# BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(notdir $(BONUS_SRCS:%.c=%.o)))
# BONUS_OBJS := $(BONUS_SRCS:bonus/%.c=$(BONUS_DIR)/%.o)

LIBFT := libft/libft.a


# OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o) $(MAIN_SRCS:%.c=%.o))
# # BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(SRCS:%.c=%.o) $(BONUS_SRCS:%.c=%.o) $(BONUS_MAIN_SRCS:%.c=%.o))
# BONUS_OBJS := $(addprefix $(BONUS_DIR)/, $(notdir $(SRCS:%.c=%.o) $(BONUS_SRCS:%.c=%.o) $(BONUS_MAIN_SRCS:%.c=%.o)))
# # GNL_OBJS := $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:%.c=%.o))
# # GC_OBJS := $(addprefix $(OBJ_DIR)/, $(GC_SRCS:%.c=%.o))

# LIBFT := libft/libft.a

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS := -Llibft -lft
#ARFLAGS := -rcs

all: $(LIBFT) $(NAME)

FRAMEWORKS := -framework OpenGL -framework AppKit

$(NAME): $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(MLX_LIB) $(FRAMEWORKS) -o $(NAME)

$(NAME): $(OBJ_DIR) $(COMMON_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(COMMON_OBJS) $(MLX_LIB) $(FRAMEWORKS) $(LDFLAGS) -o $(NAME)

# $(NAME): $(COMMON_OBJS) $(MLX_OBJS)
# 	$(CC) $(CFLAGS) $(COMMON_OBJS) $(MLX_OBJS) $(FRAMEWORKS) -o $(NAME)

# bonus: $(LIBFT) $(BONUS_DIR) $(BONUS_OBJS)
# 	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# $(BONUS_DIR)/%.o: bonus/%.c | $(BONUS_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BONUS_DIR):
	mkdir -p $(BONUS_DIR)

clean:
	$(RM) $(OBJ_DIR) $(BONUS_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) libft/_obj libft/libft.a

re: fclean submodule_update all

$(LIBFT):
	make -C libft

submodule_update:
	git submodule update --remote --merge

re_submodule: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

help:
	@echo "Makefile for $(NAME)"
	@echo "Usage:"
	@echo "	make						Build the project"
	@echo "	make bonus					Build the project with bonus functions"
	@echo "	make clean					Remove object files in the main project"
	@echo "	make fclean					Remove all build files, including libft's objects"
	@echo "	make re						Clean and rebuild the project"
	@echo "	make submodule_update				Update all submodules to the latest commit"
	@echo "	make re_submodule				Fully reset and update submodules"
	@echo "	make submodule_rebuild				Reinitialize submodules from scratch"
	@echo "	make help					Display this help message"

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all bonus clean fclean re submodule_update re_submodule submodule_rebuild help