/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:21:15 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/30 21:21:35 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

void free_token_list(t_token *head)
{
	t_token	*current;
    t_token *tmp;

    if (head == NULL)
	{
		return ;
	}
	current = head;	
	while (current != NULL)
	{
		tmp = current;
        if (current->content != NULL)
            free(current->content);
        current = current->next;
        free(tmp);
	}
}

void free_cmd_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*tmp;
	size_t		i;

	if (cmd_list == NULL)
	{
		return ;
	}
	current = cmd_list;	
	while (current != NULL)
	{
		tmp = current;
		free(current->infile);
		free(current->outfile);		
		free(current->heredoc);
		i = 0;
		while(current->args[i] != NULL)
		{
			free(current->args[i]);
			i++;
		}
		current = current->next;
		free(tmp);
	}
}

//t_command *cmd_list to be included
void free_all(char *line, t_token *token_list, t_command *cmd_list)
{
	free_token_list(token_list);
	free_cmd_list(cmd_list);
	free(line);
}
