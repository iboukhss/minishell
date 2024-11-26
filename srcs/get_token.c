#include "minishell.h"

int tokenize(char *line, t_token **token_head)
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
			//free list on failure
			return (0);
		}
		add_back(token_head, new_token);
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
	add_back(token_head, new_token);
	return (end_token - start_token);
}


void print_tokens(t_token *head)
{
	t_token	*current;

	if (head == NULL)
	{
		return ;
	}
	current = head;	
	while (current != NULL)
	{
		printf("content : %s\n",current->content);
		printf("type : %c\n", current->type);
		current = current->next;
	}
}

t_token *get_token(char *line)
{
	t_token *token_head;
	int		offset;

	token_head = NULL;
	offset = 0;
	while (*line != '\0')
	{
		if (ft_strchr(WHITESPACE, *line) == NULL)
		{
			offset = tokenize(line, &token_head);
			if (offset == 0)
			{
				//free list ; to be implemented;
				return (NULL);
			}
			line+= offset;
		}
		else
		{
			line++;
		}
		
	}
	print_tokens(token_head);
	return (token_head);
}