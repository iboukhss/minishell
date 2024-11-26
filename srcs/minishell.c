#include "minishell.h"

int	main(void)
{
	char	*line;

    while (1)
    {
        line = readline(">Enter prompt : ");
		if (!line)
		{
			break ;
		}
		if (*line)
		{
            add_history(line);
		}
		if (get_token(line) == NULL)
		{
			free(line);
			break ;
		}
		free(line);
    }
    exit(EXIT_FAILURE);
}