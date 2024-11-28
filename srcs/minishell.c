#include "minishell.h"

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
    exit(EXIT_FAILURE);
}
