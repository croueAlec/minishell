#include "minishell.h"

t_branch	*input_tree(char **input, int hd_fd, char **env)
{
	t_branch	*tree;
	t_branch	*tmp;
	t_cmd		*cmd;
	char		**cmd_split;
	int			i;

	i = 0;
	tree = NULL;
	tmp = tree;
	cmd = NULL;
	while (input[i])
	{
		cmd_split = quotes_split(input[i], ' ');
		if (!cmd_split)
			return (free_tree(tree), NULL);
		tmp = new_cmd_branch(cmd_split, hd_fd, env);
		if (i == 0)
			tree = tmp;
		cmd = tmp->elmnt;
		cmd->next_cmd = tmp;
		ft_fsplit(cmd_split);
		i++;
	}
	return (tree);
}
