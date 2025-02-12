# variables to store the names used
PROJ_NAME = minishell
LIBFT_NAME = libft.a

# directories
LIBFT_DIR = libft
PROJ_SRCS_DIR = srcs

# source files
LIBFT_SRCS = $(addprefix $(LIBFT_DIR)/, \
				ft_atoi.c \
				ft_asprintf.c \
				ft_dprintf.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_isalnum.c \
				ft_itoa.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_printf.c \
				ft_puts.c \
				ft_realloc.c \
				ft_snprintf.c \
				ft_strchr.c \
				ft_strchrnul.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strdup.c \
				ft_strfreev.c \
				ft_strjoin.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strv_length.c \
				ft_substr.c \
				ft_vasprintf.c \
				ft_vdprintf.c \
				ft_vsnprintf.c \
				ft_xasprintf.c \
				ft_xdup.c \
				ft_xdup2.c \
				ft_xfork.c \
				ft_xmalloc.c \
				ft_xpipe.c \
				ft_xrealloc.c \
				ft_xstrdup.c \
				ft_xstrdupv.c \
				ft_xstrndup.c \
				ft_xvasprintf.c \
				log_error.c \
				printf_core.c)

PROJ_SRCS = $(addprefix $(PROJ_SRCS_DIR)/, \
				builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export.c \
				builtin_pwd.c \
				builtin_unset.c \
				cmd_functions.c \
				debug.c \
				env.c \
				exec_builtin.c \
				exec_command.c \
				exec_external.c \
				exec_pipeline.c \
				exec_simple_command.c \
				exec_utils.c \
				free.c \
				get_token.c \
				minishell.c \
				parse.c \
				parse_functions.c \
				redir.c \
				redir_heredoc.c \
				sig.c \
				token_functions.c \
				token_sanitizer.c \
				token_sanitizer_functions.c)

# header files
LIBFT_HDRS = $(addprefix $(LIBFT_DIR)/, \
				libft.h \
				printf_core.h \
				get_next_line.h)

PROJ_HDRS = $(addprefix $(PROJ_SRCS_DIR)/, \
				exec.h \
				minishell.h \
				parse.h \
				sig.h \
				token.h)

# object and dependency files
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)
LIBFT_DEPS = $(LIBFT_OBJS:.o=.d)
PROJ_OBJS = $(PROJ_SRCS:.c=.o)
PROJ_DEPS = $(PROJ_OBJS:.o=.d)

# general debug c flags
CFLAGS += -Wall -Wextra -Werror

# asan flags (disabled because of conflict with valgrind)
# pass these flags via environment if necessary
#CFLAGS += -fsanitize=address,undefined

# c preprocessor flags
CPPFLAGS = -I$(LIBFT_DIR)

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
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(PROJ_NAME) $(PROJ_OBJS) $(LDLIBS) $(LDFLAGS)

clean:
	$(RM) $(LIBFT_OBJS) $(PROJ_OBJS)
	$(RM) $(LIBFT_DEPS) $(PROJ_DEPS)

fclean: clean
	$(RM) $(LIBFT_NAME)
	$(RM) $(PROJ_NAME)

re: fclean all

norm:
	-norminette $(LIBFT_HDRS) $(LIBFT_SRCS) $(PROJ_HDRS) $(PROJ_SRCS)

run: all
	./$(PROJ_NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=valgrind.supp ./$(PROJ_NAME)

test_all:
	cd mini_tester && ./runner.sh full

test_echo:
	cd mini_tester && ./runner.sh echo

test_pipe:
	cd mini_tester && ./runner.sh pipe

test_env:
	cd mini_tester && ./runner.sh env

test_syntax:
	cd mini_tester && ./runner.sh syntax

test_redir:
	cd mini_tester && ./runner.sh redir

-include $(LIBFT_DEPS) $(PROJ_DEPS)
