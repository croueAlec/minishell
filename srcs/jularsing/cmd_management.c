#include "minishell.h"

void	fill_cmd_token(char *input, t_branch *branch, char **env)
{
	t_cmd	*cmd;

	cmd = branch->elmnt;
	cmd->cmd_path = fetch_cmd_path(input, env);
}