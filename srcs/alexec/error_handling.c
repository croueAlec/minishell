/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:18:21 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 15:19:11 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(t_branch *branch, char *err_msg)
{
	ft_dprintf(2, "%s", err_msg);
	free_tree(branch);
}

void	redirection_error(t_branch *branch, char *err_msg)
{
	t_cmd	*cmd;

	ft_dprintf(2, "%s", err_msg);
	cmd = branch->elmnt;
	free(cmd->tree);
	free_cmd(cmd);
	free(branch);
}
