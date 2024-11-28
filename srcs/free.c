#include "minishell.h"

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