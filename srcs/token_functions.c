/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:49 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/30 21:19:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_back_token(t_token **token_head, t_token *new_token)
{
	t_token *current;
	if (new_token == NULL)
		return ;
	if (*token_head == NULL)
	{
		*token_head = new_token;
		return ;
	}
	current = *token_head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_token;
	new_token->next = NULL;
}

t_token	*init_token(char *content, char type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}
