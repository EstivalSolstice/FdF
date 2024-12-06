NAME := libft.a
.DEFAULT_GOAL := all
CC := cc
AR := ar
RM := rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR := _obj
INC_DIRS := . printf get_next_line
SRC_DIRS := . 

# Tell the Makefile where headers and source files are
vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################

SRCS := ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memcpy.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c ft_itoa.c 

BONUS_SRCS := 	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
				ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

GNL_SRCS := get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

PRINTF_SRCS :=	printf/ft_printf.c \
				printf/ft_check_inputprintf.c \
				printf/ft_handle_specifier.c \
				printf/ft_handle_input_c.c \
				printf/ft_handle_input_d_i.c \
				printf/ft_handle_input_p.c \
				printf/ft_handle_input_s.c \
				printf/ft_handle_input_u.c \
				printf/ft_handle_input_x.c \
				printf/ft_handle_input_xu.c \
				printf/ft_write_return_val.c \
				printf/ft_pf_itoa.c printf/ft_pf_strlen.c

SRCS += $(BONUS_SRCS) $(PRINTF_SRCS) $(GNL_SRCS)

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
# BONUS_OBJS := $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:%.c=%.o))
# GNL_OBJS := $(addprefix $(OBJ_DIR)/, $(GNL_SRCS:%.c=%.o))
# GC_OBJS := $(addprefix $(OBJ_DIR)/, $(GC_SRCS:%.c=%.o))

################################################################################
########                         COMPILING                      ################
################################################################################

# CFLAGS := -Wall -Wextra -Werror -g -MMD -MP -I$(INC_DIRS)
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP $(addprefix -I, $(INC_DIRS))
LDFLAGS :=
ARFLAGS := -rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# Rule to compile .o files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(OBJ_DIR)/printf $(OBJ_DIR)/get_next_line
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/printf:
	mkdir -p $(OBJ_DIR)/printf

$(OBJ_DIR)/get_next_line:
	mkdir -p $(OBJ_DIR)/get_next_line

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean submodule_update all

submodule_update:
	git submodule update --remote --merge

bonus: all

re_sub: submodule_rebuild

submodule_rebuild:
	git submodule deinit -f .
	git submodule update --init --recursive

-include $(OBJS:%.o=%.d)
# -include $(BONUS_OBJS:%.o=%.d)
# -include $(GNL_OBJS:%.o=%.d)

.PHONY: all clean fclean re bonus re_sub submodule_rebuild