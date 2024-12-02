/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:02 by iboukhss          #+#    #+#             */
/*   Updated: 2024/11/30 21:18:13 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int tokenize(char *line, t_token **token_list)
{
	char	*start_token;
	char	*end_token;
	char 	type;
	t_token	*new_token;

	if (*line == '\0')
		return (0);
	if (ft_strchr(ACK_SYMBOLS, *line) != NULL)
	{
		if (*line == '|')
			type = '|';
		else if (*line == '<' && *(line + 1) == '<')
			type = '+';
		else if (*line == '<')
			type = '<';
		else if (*line == '>' && *(line + 1) == '>')
			type = '-';
		else if (*line == '>')
			type = '>';
		else
			return (0);
		if (type == '+' || type == '-')
			new_token = init_token(ft_substr(line, 0, 2), type);
		else
			new_token = init_token(ft_substr(line, 0, 1), type);
		if (new_token == NULL)
		{
			return (0);
		}
		add_back(token_list, new_token);
		return (type == '+' || type == '-') ? 2 : 1;
	}
	start_token = line;
	while (*line != '\0' && ft_strchr(WHITESPACE, *line) == NULL && ft_strchr(ACK_SYMBOLS, *line) == NULL
		&& ft_strchr(NAK_SYMBOLS, *line) == NULL)
		line++;
	end_token = line;
	new_token = init_token(ft_substr(start_token, 0, end_token - start_token), 'w');
	if (new_token == NULL)
		return (0);
	add_back(token_list, new_token);
	return (end_token - start_token);
}

t_token *get_token(char *line)
{
	t_token *token_list;
	int		offset;

	token_list = NULL;
	offset = 0;
	while (*line != '\0')
	{
		if (ft_strchr(WHITESPACE, *line) == NULL)
		{
			offset = tokenize(line, &token_list);
			if (offset == 0)
			{
				return (NULL);
			}
			line+= offset;
		}
		else
		{
			line++;
		}
		
	}
	print_token_list(token_list);
	return (token_list);
}
