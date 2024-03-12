#include "minishell.h"

void	generate_cmd_branches(t_branch *first, int len)
{
	t_branch	*tmp;
	t_cmd		*cmd;
	int			i;

	i = 0;
	tmp = first;
	while (i < len)
	{
		tmp = new_cmd_branch();
		cmd = tmp->elmnt;
		tmp = cmd->next_cmd;
		i++;
	}
}
/*
t_branch	*input_tree(char **input, char **env)
{
	t_branch	*first;
	t_branch	*tmp;
	t_cmd		*cmd;
	int			len;
	int			i;

	i = 0;
	len = str_tab_len(input);
	generate_cmd_branches(first, len);
	tmp = first;
	while (i < len)
	{
		fill_cmd_token(input[i], tmp, env);
		cmd = tmp->elmnt;
		tmp = cmd->next_cmd;
		i++;
	}
	return (first);
}*/