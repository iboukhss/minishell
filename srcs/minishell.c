/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/30 21:20:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*line;
	t_token *token_list;

    while (1)
    {
        line = readline(">Enter prompt : ");
		if (!line)
			break ;
		if (*line)
		{
            add_history(line);
			token_list = get_token(line);
			if (token_list == NULL)
			{
				free_all(line, token_list);
				break ;
			}
		}
		free_all(line, token_list);
    }
    return (0);
}
