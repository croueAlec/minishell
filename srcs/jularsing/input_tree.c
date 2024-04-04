/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:38:44 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/04 13:38:46 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i] != 0)
		i++;
	return (i);
}

t_branch	*new_cmd_branch(char *cmd, t_hd_fd_list *hd_fd_list, char **env)
{
	t_branch	*node;
	char		**cmd_split;

	cmd_split = quotes_split(cmd, ' ');
	if (!cmd_split)
		return (NULL);
	node = ft_calloc(1, sizeof(t_branch));
	if (!node)
		return (ft_fsplit(cmd_split), NULL);
	node->type = T_CMD;
	node->elmnt = new_cmd(cmd_split, hd_fd_list, env);
	if (!node->elmnt)
		return (ft_fsplit(cmd_split), free(node), NULL);
	return (ft_fsplit(cmd_split), node);
}


t_branch	*input_tree(char **input, t_hd_fd_list *hd_fd_list, char **env)
{
	t_branch	*tree;
	t_branch	*new_branch;
	t_cmd		*prev_cmd;
	int			i;

	i = 0;
	tree = NULL;
	new_branch = NULL;
	prev_cmd = NULL;
	while (input[i])
	{
		new_branch = new_cmd_branch(input[i], hd_fd_list, env);
		if (!new_branch)
			return (free_tree(tree), NULL);
		if (prev_cmd)
			prev_cmd->next_cmd = new_branch;
		if (i == 0)
			tree = new_branch;
		prev_cmd = new_branch->elmnt;
		i++;
	}
	return (tree);
}
