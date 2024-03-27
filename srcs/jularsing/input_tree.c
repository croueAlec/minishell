#include "minishell.h"

int	str_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != 0)
		i++;
	return (i);
}

t_branch	*new_cmd_branch(char **cmd_split, int hd_fd, char **env)
{
	t_branch	*node;

	node = ft_calloc(1, sizeof(t_branch));
	if (!node)
		return (NULL);
	node->type = T_CMD;
	node->elmnt = new_cmd(cmd_split, hd_fd, env);
	return (node);
}


t_branch	*input_tree(char **input, int hd_fd, char **env)
{
	t_branch	*tree;
	t_branch	*new_branch;
	t_cmd		*prev_cmd;
	char		**cmd_split;
	int			i;

	i = 0;
	tree = NULL;
	new_branch = NULL;
	prev_cmd = NULL;
	while (input[i])
	{
		cmd_split = quotes_split(input[i], ' ');
		if (!cmd_split)
			return (free_tree(tree), NULL);
		new_branch = new_cmd_branch(cmd_split, hd_fd, env);
		if (prev_cmd)
			prev_cmd->next_cmd = new_branch;
		if (i == 0)
			tree = new_branch;
		prev_cmd = new_branch->elmnt;
		ft_fsplit(cmd_split);
		i++;
	}
	return (tree);
}
