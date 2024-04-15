/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:08:42 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 11:19:05 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*handle_cmd_not_found(t_branch *branch)
{
	t_cmd	*cmd;
	int		is_directory;

	cmd = branch->elmnt;
	is_directory = is_cmd_path(cmd->args[0], '/');
	if (is_directory || is_path_unset(cmd->env))
	{
		cmd->env->err_no = 127;
		ft_dprintf(2, NO_SUCH_FILE_OR_DIR, cmd->args[0]);
		return (return_next_cmd(branch));
	}
	else if (!is_directory)
	{
		cmd->env->err_no = 127;
		ft_dprintf(2, CMD_NOT_FOUND, cmd->args[0]);
		return (return_next_cmd(branch));
	}
	return (cmd);
}
