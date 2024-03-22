/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_test_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:08:29 by acroue            #+#    #+#             */
/*   Updated: 2024/03/22 14:08:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec_unit_test.h"

void	define_test_pipe(t_cmd *cmd, char **args)
{
	t_branch	*next_cmd;

	next_cmd = ft_calloc(sizeof(t_branch), 1);
	cmd->next_cmd = define_test_cmd(next_cmd, args, 1);
}
