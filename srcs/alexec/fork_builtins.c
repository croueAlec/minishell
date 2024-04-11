/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/11 16:40:11 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_built_ins(int fd_out, t_branch *branch, size_t *cmd_number)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		err_no;

	pid = UNDEFINED_FD;
	cmd = branch->elmnt;
	if (fd_out < 0)
		fd_out = STDOUT_FILENO;
	if (cmd && (cmd->next_cmd || *cmd_number))
		pid = fork();
	if (cmd && (cmd->next_cmd || *cmd_number) && pid == 0)
	{
		cmd->env->err_no = handle_builtins(branch, cmd_number, fd_out);
		err_no = cmd->env->err_no;
		free_env(cmd->env);
		free_tree(branch);
		exit(err_no);
	}
	else if (cmd && (!cmd->next_cmd && !*cmd_number))
	{
		cmd->env->err_no = handle_builtins(branch, cmd_number, fd_out);
	}
	free_tree(branch);
	(*cmd_number)++;
	return (pid);
}
