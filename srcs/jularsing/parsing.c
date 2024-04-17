/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:15:55 by acroue            #+#    #+#             */
/*   Updated: 2024/04/17 04:18:44 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_white_space_str(char *s)
{
	if (s)
	{
		while (*s == ' ' || (*s >= 9 && *s <= 13))
			s++;
		if (*s == 0)
			return (1);
		return (0);
	}
	return (-1);
}

static void	err_no_sigint_in_prompt(t_env *env)
{
	if (g_global == SIGINT)
		env->err_no = 130;
}

t_branch	*parsing(t_env *env)
{
	char			*input;
	char			**cmds;
	t_branch		*tree;
	t_hd_fd_list	*hd_fd_list;

	hd_fd_list = NULL;
	input = readline("tacOS > ");
	if (!input && ft_dprintf(2, "exit\n"))
		free_and_exit(env->err_no, NULL, env);
	err_no_sigint_in_prompt(env);
	if (is_white_space_str(input) == 1)
		return (NULL);
	if (is_line_empty(input))
		add_history(input);
	if (all_quotes_are_closed(input) == 0
		|| no_syntax_error(input, &hd_fd_list, env) == 0)
		return (free(input), NULL);
	cmds = quotes_split(input, '|');
	if (cmds == 0)
		return (free(input), NULL);
	tree = input_tree(cmds, hd_fd_list, env);
	if (!tree)
		return (ft_fsplit(cmds), free(input), NULL);
	return (ft_fsplit(cmds), free(input), tree);
}
