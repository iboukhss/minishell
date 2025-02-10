/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:21:15 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:18:42 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include <stdlib.h>

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(head->content);
		head = head->next;
		free(tmp);
	}
}

void	free_cmd_list(t_command *cmd_list)
{
	t_command	*tmp;
	size_t		i;

	while (cmd_list != NULL)
	{
		tmp = cmd_list;
		free(cmd_list->infile);
		free(cmd_list->outfile);
		free(cmd_list->heredoc);
		i = 0;
		while (cmd_list->args[i] != NULL)
		{
			free(cmd_list->args[i]);
			i++;
		}
		cmd_list = cmd_list->next;
		free(tmp);
	}
}

//t_command *cmd_list to be included
void	free_all(char *line, t_token *token_list, t_command *cmd_list)
{
	if (token_list != NULL)
		free_token_list(token_list);
	if (cmd_list != NULL)
		free_cmd_list(cmd_list);
	if (line != NULL)
		free(line);
}
