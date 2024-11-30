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

void free_all(char *line, t_token *token_list)
{
    free_token_list(token_list);
    free(line);
}
