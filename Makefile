# variables to store the names used
PROJ_NAME = minishell
LIBFT_NAME = libft.a
GREEN = \033[32m
RESET = \033[0m

# directories
LIBFT_DIR = libft
PROJ_SRCS_DIR = srcs

# source files
LIBFT_SRCS = $(addprefix $(LIBFT_DIR)/, \
				ft_memcpy.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strfreev.c \
				ft_strlen.c \
				ft_strlenv.c \
				ft_strlcpy.c \
				ft_strchr.c \
				ft_strchrnul.c \
				ft_substr.c \
				ft_xmalloc.c \
				ft_xstrdup.c \
				ft_xstrdupv.c \
				ft_strncmp.c)

PROJ_SRCS = $(addprefix $(PROJ_SRCS_DIR)/, \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export.c \
				builtin_unset.c \
				exec_command.c \
				minishell.c \
				setup_redirections.c \
				get_token.c \
				debug.c \
				free.c \
				token_functions.c \
				cmd_functions.c \
				parser.c)

# header files
LIBFT_INCS = $(addprefix $(LIBFT_DIR)/, libft.h)

PROJ_INCS = $(addprefix $(PROJ_SRCS_DIR)/, \
				exec.h \
				minishell.h)

# object and dependency files
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
LIBFT_DEPS = $(LIBFT_OBJS:.o=.d)
PROJ_OBJS = $(PROJ_SRCS:.c=.o)
PROJ_DEPS = $(PROJ_OBJS:.o=.d)

# general c flags (no -Werror)
CFLAGS = -Wall -Wextra

# debug c flags (full debug with sanitizers and dependency generation)
CFLAGS += -g3 -fsanitize=address,undefined -MMD

# include dirs
CFLAGS += -I$(LIBFT_DIR)

# linker flags
LDLIBS = -L.
LDFLAGS = -lreadline -lft

# archiver flags
ARFLAGS = rcs

# phony targets
.PHONY: all clean fclean re norm run val

# default target 
all: $(PROJ_NAME)

$(LIBFT_NAME): $(LIBFT_OBJS)
	$(AR) $(ARFLAGS) $(LIBFT_NAME) $(LIBFT_OBJS)

# rules to build my project
$(PROJ_NAME): $(LIBFT_NAME) $(PROJ_OBJS)
	$(CC) $(CFLAGS) -o $(PROJ_NAME) $(PROJ_OBJS) $(LDLIBS) $(LDFLAGS)
	@echo " "
	@echo "$(GREEN)     ========>>>>>> PROJECT COMPILED SUCCESSFULLY <<<<<<========      "
	@echo "$(RESET)"

clean:
	$(RM) $(PROJ_OBJS) $(PROJ_DEPS)
	$(RM) $(LIBFT_OBJS) $(LIBFT_DEPS)

fclean: clean
	$(RM) $(PROJ_NAME)
	$(RM) $(LIBFT_NAME)

re: fclean all

norm:
	-norminette $(LIBFT_SRCS) $(LIBFT_INCS) $(PROJ_SRCS) $(PROJ_INCS)

run: all
	./$(PROJ_NAME)

val: all
	valgrind ./$(PROJ_NAME)

-include $(LIBFT_DEPS) $(PROJ_DEPS)
