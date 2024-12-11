/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:19:50 by iboukhss          #+#    #+#             */
/*   Updated: 2024/12/11 11:07:52 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char		*line;
	t_token		*token_list;
	t_command	*cmd_list;

	token_list = NULL;
	cmd_list = NULL;

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
				free(line);
				break ;
			}
			//print_token_list(token_list);
			cmd_list = parsing_tokens(token_list);
			if (cmd_list == NULL)
			{
				free(token_list);
				free(line);
				break ;
			}
			print_cmd_list(cmd_list);
		}
		free_all(line, token_list, cmd_list);
    }
    return (0);
}
