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

#ifndef PARSE_H
# define PARSE_H

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

int			tokenize(char *line, t_token **token_list, t_shell *shell);
char		*tokenize_ack_sym(t_token **token_list, char *line);
char		*tokenize_quotes(t_token **token_list, char *line, char quote);
char		*tokenize_content(t_token **token_list, char *line, t_shell *shell);
char		*scan_quote(char *line, char quote);
char		*sanitize_token_content(char *line, char *end, t_shell *shell);
void		add_back_token(t_token **token_list, t_token *new_token);
void		add_back_cmd(t_command **cmd_head, t_command *new_cmd);
void		print_token_list(t_token *token_list);
void		print_cmd_list(t_command *cmd_list);
void		free_all(char *line, t_token *token_list, t_command *cmd_list);
void		free_token_list(t_token *head);
void		free_cmd_list(t_command *cmd_list);
void		free_shell(t_shell *shell);
t_token		*get_token(char *line, t_shell *shell);
t_token		*init_token(char *content, char type);
t_command	*init_cmd(void);
t_command	*parsing_tokens(t_token *token_list);

#endif
