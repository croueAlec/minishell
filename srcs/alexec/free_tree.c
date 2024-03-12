/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:22:08 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 15:19:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->cmd_path);
	free_tab((void **)cmd->args);
	free(cmd);
}

void	free_tree(t_branch *branch)
{
	t_cmd		*cmd;
	t_branch	**tree;
	size_t		i;

	i = 0;
	if (branch->type != T_CMD)
		return ((void)printf("Error free branch type does not match"));
	cmd = branch->elmnt;
	tree = cmd->tree;
	while (tree && tree[i] != NULL)
	{
		printf("%d\n", tree[i]->type);
		if (tree[i]->type == T_INFILE)
			free_infile_leaves(tree[i]->elmnt);
		else if (tree[i]->type == T_OUTFILE)
			free_outfile_leaves(tree[i]->elmnt);
		else if (tree[i]->type == T_PIPE && printf("Pipe free ???"))
			continue ;
		free(tree[i]);
		i++;
	}
	free(tree);
	free_cmd(cmd);
	free(branch);
}
