/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:07:41 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:38:04 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MS_XSUCCESS	0		// Exit success
# define MS_XFAILURE	1		// Catchall for general errors
# define MS_XBADUSAGE	2		// Misuse of shell builtin
# define MS_XNOEXEC		126		// Command found but not executable
# define MS_XNOTFOUND	127		// Command not found
# define MS_XINVAL		128		// Invalid exit argument
# define MS_XRANGE		255		// Exit status out of range (0-255)

# define MAX_ARGS 50

// Try to keep includes as lean as possible (only add typedef includes here)
// stdlib.h, unistd.h, libft.h, ect. should remain in their own respective file
// scopes
# include <stdbool.h>
# include <stddef.h>

// Forward declarations here
typedef struct s_command	t_command;

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
	t_command	*next;				// Next command in the pipeline (|)
}	t_command;

#endif
