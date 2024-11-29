# variables to store the names used
NAME_MY_PROJECT = minishell
NAME_LIBFT = libft.a
GREEN = \033[32m
RESET = \033[0m

# directories
MY_LIBFT_DIR = libft
MY_SRCS_DIR = srcs
CUR_DIR = $(shell pwd)

# files used
MY_LIBFT_SRCS = $(addprefix $(MY_LIBFT_DIR)/, \
				ft_memcpy.c \
				ft_strdup.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strchr.c \
				ft_strchrnul.c \
				ft_substr.c)

MY_PROJECT_SRCS = $(addprefix $(MY_SRCS_DIR)/, \
				minishell.c \
				get_token.c \
				debug.c \
				free.c \
				token_functions.c)

# object and dependency files
MY_LIBFT_OBJS = $(MY_LIBFT_SRCS:.c=.o)
MY_PROJECT_OBJS = $(MY_PROJECT_SRCS:.c=.o)
MY_PROJECT_DEPS = $(MY_PROJECT_OBJS:.o=.d)

# general c flags (no -Werror)
CFLAGS = -Wall -Wextra

# debug c flags (full debug with sanitizers and dependency generation)
CFLAGS += -g3 -fsanitize=address,undefined -MMD

# include dirs
CFLAGS += -I$(MY_LIBFT_DIR)

# linker flags
LDFLAGS = -lreadline

# compiler used
CC = cc

# phony targets
.PHONY: all clean fclean re

# default target 
all: $(NAME_MY_PROJECT)

$(NAME_LIBFT): $(MY_LIBFT_OBJS)
	ar rcs $(NAME_LIBFT) $(MY_LIBFT_OBJS)

# rules to build my project
$(NAME_MY_PROJECT): $(NAME_LIBFT) $(MY_PROJECT_OBJS)
	$(CC) $(CFLAGS) -o $(NAME_MY_PROJECT) $(MY_PROJECT_OBJS) $(MY_LIBFT_OBJS) $(LDFLAGS)
	@echo " "
	@echo "$(GREEN)     ========>>>>>> PROJECT COMPILED SUCCESSFULLY <<<<<<========      "
	@echo "$(RESET)"

# compile libft object files
$(MY_LIBFT_DIR)/%.o: $(MY_LIBFT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# compile my project object files
$(MY_SRCS_DIR)/%.o : $(MY_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MY_PROJECT_OBJS)
	rm -f $(MY_LIBFT_OBJS)

fclean: clean
	rm -f $(NAME_MY_PROJECT)
	rm -f $(NAME_LIBFT)

re: fclean all

run:
	make
	./minishell

val:
	make
	valgrind ./minishell

-include $(MY_PROJECT_DEPS)
