/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:26 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/30 21:18:35 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

void print_token_list(t_token *token_list)
{
	t_token	*current;

	if (token_list == NULL)
	{
		return ;
	}
	current = token_list;	
	while (current != NULL)
	{
		printf("content = %s, type : %c\n",current->content, current->type);
		current = current->next;
	}
}
