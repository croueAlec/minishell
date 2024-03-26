#include "minishell.h"

int	str_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != 0)
		i++;
	return (i);
}

/*
t_branch	*new_cmd_branch(void)
{
	t_branch	*node;

	node = ft_calloc(1, sizeof(t_branch));
	if (!node)
		return (NULL);
	node->type = T_CMD;
	node->elmnt = new_cmd();
	return (node);
}
*/