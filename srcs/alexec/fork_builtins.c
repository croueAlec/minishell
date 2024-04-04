/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/04 13:52:40 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_built_ins(int	fd_in, t_branch *branch)
{
	if (fd_in < 0)
		fd_in = STDIN_FILENO;
	ft_dprintf(fd_in, "d builtin\n");
	free_tree(branch);
}
