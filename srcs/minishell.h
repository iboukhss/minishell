/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:07:41 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/02 16:55:05 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define WHITESPACE " \t\r\n\v"
# define QUOTES "\'\""
# define ACK_SYMBOLS "<|>"
# define NAK_SYMBOLS "&;"
# define MAX_ARGS 50

// Try to keep includes as lean as possible (only add typedef includes here)
// stdlib.h, unistd.h, libft.h, ect. should remain in their own respective file scopes
# include <stdbool.h>
# include <stddef.h>

// Forward declarations here
typedef struct s_command	t_command;
typedef struct s_token		t_token;

typedef struct s_shell
{
	char	**envs;				// Current shell environment variables
	int		exit_status;		// Last command exit status ($?)
}	t_shell;

typedef struct s_command
{
	char		*args[MAX_ARGS];	// Command and arguments
	bool		is_builtin;			// Flag for builtins (echo, cd, pwd, ect.)
	char		*infile;			// Input redirection file (<)
	char		*outfile;			// Output redirection file (>)
	bool		append_mode;		// Flag for append mode (>>)
	char		*heredoc;			// Heredoc delimiter (<<)
	t_command	*next;				// Pointer to next command in the pipeline (|)
}	t_command;

typedef struct s_token
{
	char	*content;
	char	type;
	t_token	*next;
}	t_token;

int			tokenize(char *line, t_token **token_list, t_shell *shell);
char 		*tokenize_ack_sym(t_token **token_list, char *line);
char 		*tokenize_quotes(t_token **token_list, char *line, char quote);
char		*tokenize_content(t_token **token_list, char *line, t_shell *shell);
char 		*scan_quote(char *line, char quote);
char 		*sanitize_token_content(char *line, char *end, t_shell *shell);
char		*get_env(const char *key, t_shell *shell);
void		add_back_token(t_token **token_list, t_token *new_token);
void		add_back_cmd(t_command **cmd_head, t_command *new_cmd);
void		print_token_list(t_token *token_list);
void		print_cmd_list(t_command *cmd_list);
void		free_all(char *line, t_token *token_list, t_command *cmd_list);
void		free_token_list(t_token *head);
void		free_cmd_list(t_command *cmd_list);
void		free_shell(t_shell *shell);
t_token 	*get_token(char *line, t_shell *shell);
t_token		*init_token(char *content, char type);
t_shell	*init_shell(char **envp);

t_command	*init_cmd(void);
t_command	*parsing_tokens(t_token *token_list);

#endif
