/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:31:22 by acroue            #+#    #+#             */
/*   Updated: 2024/04/02 17:49:47 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_cmd_path(char *cmd, char ch)
{
	size_t	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Sets the values of the FDs to UNDEFINED_FD (-2).
 */
void	define_execution_fd(int *fd_one, int *fd_two, int *fd_three)
{
	if (fd_one)
		*fd_one = UNDEFINED_FD;
	if (fd_two)
		*fd_two = UNDEFINED_FD;
	if (fd_three)
		*fd_three = UNDEFINED_FD;
}

t_cmd	*return_next_cmd(t_branch *branch)
{
	t_branch	*next_branch;
	t_cmd		*curr_cmd;
	t_cmd		*next_cmd;

	curr_cmd = branch->elmnt;
	next_branch = curr_cmd->next_cmd;
	if (!next_branch)
		return ((void)ft_dprintf(2, "Not supposed to happen (ERR48)\n"), NULL);
	next_cmd = next_branch->elmnt;
	branch->elmnt = next_cmd;
	free_file_tree(curr_cmd->tree);
	free_cmd(curr_cmd);
	return (next_cmd);
}
