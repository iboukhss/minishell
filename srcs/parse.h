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

# include "minishell.h"
# include "token.h"

void		add_back_cmd(t_command **cmd_head, t_command *new_cmd);
int			append(t_token **token, t_command *cmd);
int			heredoc(t_token **token, t_command *cmd);
int			outfile(t_token **token, t_command *cmd);
int			infile(t_token **token, t_command *cmd);
int			is_builtin(t_token *token);
int			add_arg(t_command *cmd, t_token *token);
int			check_syntax_errors(t_token *token_list, t_shell *shell);
int			build_cmd(t_token **token, t_command *cmd);
t_command	*parsing_tokens(t_token *token_list, t_shell *shell);
t_command	*init_cmd(void);

#endif
