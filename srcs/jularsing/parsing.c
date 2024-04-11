/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:15:55 by acroue            #+#    #+#             */
/*   Updated: 2024/04/10 15:00:16 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_branch	*parsing(t_env *env)
{
	char			*input;
	char			**cmds;
	t_branch		*tree;
	t_hd_fd_list	*hd_fd_list;

	hd_fd_list = NULL;
	input = readline("tacOS > ");
	if (all_quotes_are_closed(input) == 0
		|| no_syntax_error(input, &hd_fd_list, env->env_tab) == 0)
		return (free(input), NULL);
	cmds = quotes_split(input, '|');
	if (cmds == 0)
		return (free(input), NULL);
	tree = input_tree(cmds, hd_fd_list, env);
	if (!tree)
		return (ft_fsplit(cmds), free(input), NULL);
	return (ft_fsplit(cmds), free(input), tree);
}
