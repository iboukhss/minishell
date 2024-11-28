#include "minishell.h"

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