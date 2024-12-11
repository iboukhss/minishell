#include "minishell.h"

void add_back_cmd(t_command **cmd_head, t_command *new_cmd)
{
	t_command *current;
	if (new_cmd == NULL)
		return ;
	if (*cmd_head == NULL)
	{
		*cmd_head = new_cmd;
		return ;
	}
	current = *cmd_head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_cmd;
	new_cmd->next = NULL;
}

t_command	*init_cmd(void)
{
	t_command   *cmd;
    size_t      i;

	cmd = ft_xmalloc(sizeof(t_command));
    i = 0;
    while (i < MAX_ARGS)
    {
        cmd->args[i] = NULL;
        i++;
    }
    cmd->append_mode = 0;
    cmd->heredoc = NULL;
    cmd->infile = NULL;
    cmd->is_builtin = 0;
    cmd->next = NULL;
    cmd->outfile = NULL;
	return (cmd);
}
