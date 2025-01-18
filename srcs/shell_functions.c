#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_xmalloc(sizeof(*shell));
	shell->envs = ft_xstrdupv(envp);
	shell->exit_status = 0;
	return (shell);
}

void	free_shell(t_shell *shell)
{
	ft_strfreev(shell->envs);
	free(shell);
}
