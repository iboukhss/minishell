#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

#define WHITESPACE " \t\r\n\v"
#define ACK_SYMBOLS "<|>"
#define NAK_SYMBOLS "&/;"

typedef struct  s_token t_token;

typedef struct  s_token
{
	char	*content;
	char 	type;
	t_token *next;
}				t_token;

int		tokenize(char *line, t_token **token_list);
void	add_back(t_token **token_list, t_token *new_token);
void	print_token_list(t_token *token_list);
void	free_all(char *line, t_token *token_list);
void	free_token_list(t_token *head);
t_token	*get_token(char *line);
t_token	*init_token(char *content, char type);


#endif
