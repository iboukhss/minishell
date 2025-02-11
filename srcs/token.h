/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:09:31 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:38:29 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# define WHITESPACE " \t\r\n\v"
# define QUOTES "\'\""
# define ACK_SYMBOLS "<|>"
# define NAK_SYMBOLS "&;"

# include "minishell.h"

typedef struct s_token	t_token;

typedef struct s_token
{
	char	*content;
	char	type;
	t_token	*next;
}	t_token;

char	*scan_quote(char *line, char quote);
char	*concat_content(char *content, char *start, size_t i);
char	*expand_var(char *var_start, size_t *var_name_len, t_shell *shell);
char	*handle_variable(char *content, char **start, char *c, t_shell *shell);
char	*handle_quotes(char *content, char **start, char *c, bool *quote_flag);
char	*get_exit(char *content, char **start, char *c, t_shell *shell);
char	*sanitize_token_content(char *line, char *end, t_shell *shell);
char	*tokenize_ack_sym(t_token **token_list, char *line);
char	*tokenize_content(t_token **token_list, char *line, t_shell *shell);
int		set_type(char *line, char *type);
int		tokenize(char *line, t_token **token_list, t_shell *shell);
void	add_back_token(t_token **token_head, t_token *new_token);
void	init_variables(char *line, char **start, char **content, size_t *i);
void	init_bool(bool *in_single, bool*in_double);
t_token	*get_token(char *line, t_shell *shell);
t_token	*init_token(char *content, char type);

#endif
