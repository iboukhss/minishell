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
# define ACK_SYMBOLS "<|>"
# define NAK_SYMBOLS "&/;"

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
	char		**args;			// Command and arguments
	bool		is_builtin;		// Flag for builtins (echo, cd, pwd, ect.)
	char		*infile;		// Input redirection file (<)
	char		*outfile;		// Output redirection file (>)
	bool		append_mode;	// Flag for append mode (>>)
	char		*heredoc;		// Heredoc delimiter (<<)
	t_command	*next;			// Pointer to next command in the pipeline (|)
}	t_command;

typedef struct s_token
{
	char	*content;
	char	type;
	t_token	*next;
}	t_token;

int		tokenize(char *line, t_token **token_list);
void	add_back(t_token **token_list, t_token *new_token);
void	print_token_list(t_token *token_list);
void	free_all(char *line, t_token *token_list);
void	free_token_list(t_token *head);
t_token	*get_token(char *line);
t_token	*init_token(char *content, char type);

#endif
