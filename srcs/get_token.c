/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck    <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:18:02 by iboukhss          #+#    #+#             */
/*   Updated: 2025/01/31 18:19:08 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#include "libft.h"
#include <stdio.h>

char	*tokenize_ack_sym(t_token **token_list, char *line)
{
	char	type;
	t_token	*new_token;

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
		return (NULL);
	if (type == '+' || type == '-')
		new_token = init_token(ft_substr(line, 0, 2), type);
	else
		new_token = init_token(ft_substr(line, 0, 1), type);
	if (new_token == NULL)
		return (NULL);
	add_back_token(token_list, new_token);
	if (type == '+' || type == '-')
		return (line + 2);
	return (line + 1);
}

char	*tokenize_content(t_token **token_list, char *line, t_shell *shell)
{
	char	*start_token;
	char	*end_token;
	char	*content;
	t_token	*new_token;

	start_token = line;
	while (*line != '\0' && ft_strchr(WHITESPACE, *line) == NULL
		&& ft_strchr(ACK_SYMBOLS, *line) == NULL
		&& ft_strchr(NAK_SYMBOLS, *line) == NULL)
	{
		if (*line == '\'' || *line == '\"')
		{
			line = scan_quote(line, *line);
			if (line == NULL)
				return (NULL);
		}
		else
			line++;
	}
	end_token = line;
	content = sanitize_token_content(start_token, end_token, shell);
	new_token = init_token(content, 'w');
	add_back_token(token_list, new_token);
	return (end_token);
}

int	tokenize(char *line, t_token **token_list, t_shell *shell)
{
	char	*end_token;

	end_token = NULL;
	if (*line == '\0')
		return (0);
	if (ft_strchr(ACK_SYMBOLS, *line) != NULL)
		end_token = tokenize_ack_sym(token_list, line);
	else
		end_token = tokenize_content(token_list, line, shell);
	if (end_token == NULL)
		return (0);
	return (end_token - line);
}

t_token	*get_token(char *line, t_shell *shell)
{
	t_token	*token_list;
	int		offset;

	token_list = NULL;
	offset = 0;
	while (*line != '\0')
	{
		if (ft_strchr(WHITESPACE, *line) == NULL)
		{
			offset = tokenize(line, &token_list, shell);
			if (offset == 0)
			{
				free_token_list(token_list);
				return (NULL);
			}
			line = line + offset;
		}
		else
		{
			line++;
		}
	}
	return (token_list);
}
