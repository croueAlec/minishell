/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:15:55 by acroue            #+#    #+#             */
/*   Updated: 2024/04/03 16:00:45 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_branch	*parsing(char **env)
{
	char		*input;
	char		**cmds;
	t_branch	*tree;
	int			hd_fd;

	input = readline("tacos > ");
	/*
	ADD HEREDOC MANAGEMENT
	if (isheredoc == TRUE)
	{
		ft_heredoc();
	}
	else */
		hd_fd = -2;
	if (all_quotes_are_closed(input) == 0 || no_syntax_error(input) == 0)
		return (NULL);
	cmds = quotes_split(input, '|');
	if (cmds == 0)
		return (free(input), NULL);
	tree = input_tree(cmds, hd_fd, env);
	if (!tree)
		return (ft_fsplit(cmds), free(input), NULL);
	return (ft_fsplit(cmds), free(input), tree);
}
