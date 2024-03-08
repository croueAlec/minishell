/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:18:21 by acroue            #+#    #+#             */
/*   Updated: 2024/03/08 18:28:06 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(t_branch *branch, char *err_msg)
{
	ft_dprintf(2, "%s", err_msg);
	free_tree(branch);
}

/**
 * @brief In case of a redirection error (invalid permissions, missing file...) 
 * this function frees the parent Command Branch and all of it's contents
 * 
 * @param branch The branch command structure to be freed
 * @param tree_index The index of the failing infile from whence to free
 * @param err_msg The error message to display when the function is called
 */
void	redirection_error(t_branch *branch, size_t tree_index, char *err_msg)
{
	t_cmd	*cmd;

	ft_dprintf(2, "%s", err_msg);
	cmd = branch->elmnt;
	free_tab(&cmd->tree[tree_index]);
	free(cmd->tree);
	free_cmd(cmd);
	free(branch);
}
