/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:09:31 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:38:29 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "token.h"
# include "minishell.h"

void		free_all(char *line, t_token *token_list, t_command *cmd_list);
void		free_token_list(t_token *head);
void		free_cmd_list(t_command *cmd_list);
void		free_shell(t_shell *shell);

#endif
