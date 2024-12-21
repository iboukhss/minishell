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
#include <stdio.h>

//init i = 1 to move to the next char following the quote identified

char *tokenize_ack_sym(t_token **token_list, char *line)
{
	char type;
	t_token *new_token;

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

char *tokenize_quotes(t_token **token_list, char *line, char quote)
{
	char *end_token;
	t_token *new_token;

	end_token = scan_quote(line, quote);
	if (end_token == NULL)
		return (NULL);
	new_token = init_token(ft_substr(line, 0, end_token - line), 'w');
	if (new_token == NULL)
	{
		return (NULL);
	}
	add_back_token(token_list, new_token);
	return (end_token);
}

char *tokenize_content(t_token **token_list, char *line)
{
	char *start_token;
	char *end_token;
	t_token *new_token;

	start_token = line;
	while (*line != '\0' && ft_strchr(WHITESPACE, *line) == NULL && ft_strchr(ACK_SYMBOLS, *line) == NULL
		&& ft_strchr(NAK_SYMBOLS, *line) == NULL)
		line++;
	end_token = line;
	new_token = init_token(ft_substr(start_token, 0, end_token - start_token), 'w');
	if (new_token == NULL)
		return (NULL);
	add_back_token(token_list, new_token);
	return (end_token);
}

int tokenize(char *line, t_token **token_list)
{
	char	*end_token;

	end_token = NULL;
	if (*line == '\0')
		return (0);
	if (*line == '\'' || *line == '\"')
		end_token = tokenize_quotes(token_list, line, *line);		
	else if (ft_strchr(ACK_SYMBOLS, *line) != NULL)
		end_token = tokenize_ack_sym(token_list, line);
	else
		end_token = tokenize_content(token_list, line);
	if (end_token == NULL)
			return (0);
	return (end_token - line);
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
				free_token_list(token_list);
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
