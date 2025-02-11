/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:26 by dheck             #+#    #+#             */
/*   Updated: 2025/02/11 15:21:28 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "libft.h"
#include <stdio.h>

int	infile(t_token **token, t_command *cmd)
{
	if (token == NULL || (*token) == NULL || (*token)->next == NULL)
		return (0);
	cmd->infile = ft_xstrdup(((*token)->next)->content);
	*token = (*token)->next;
	return (1);
}

int	outfile(t_token **token, t_command *cmd)
{
	if (token == NULL || (*token) == NULL || (*token)->next == NULL)
		return (0);
	cmd->outfile = ft_xstrdup(((*token)->next)->content);
	*token = (*token)->next;
	return (1);
}

int	append(t_token **token, t_command *cmd)
{
	if (token == NULL || (*token) == NULL || (*token)->next == NULL)
		return (0);
	cmd->append_mode = 1;
	cmd->outfile = ft_xstrdup(((*token)->next)->content);
	*token = (*token)->next;
	return (1);
}

int	heredoc(t_token **token, t_command *cmd)
{
	if (token == NULL || (*token) == NULL || (*token)->next == NULL)
		return (0);
	cmd->heredoc = ft_xstrdup(((*token)->next)->content);
	*token = (*token)->next;
	return (1);
}
