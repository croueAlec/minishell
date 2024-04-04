/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/04 18:42:10 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_built_ins(int	fd_out, t_branch *branch, size_t *cmd_number)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = branch->elmnt;
	if (fd_out < 0)
		fd_out = STDOUT_FILENO;
	if (cmd && (cmd->next_cmd || *cmd_number))
		pid = fork();
	if (cmd && (cmd->next_cmd || *cmd_number) && pid == 0)
	{
		handle_builtins(branch, cmd_number, fd_out);
	}
	else if (cmd && (!cmd->next_cmd && !*cmd_number))
	{
		handle_builtins(branch, cmd_number, fd_out);
	}
	free_tree(branch);
}
