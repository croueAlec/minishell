/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:56:32 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 17:35:27 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit_first_arg(char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-' && arg[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	free_and_exit(int code, t_branch *branch, t_env *env)
{
	if (env)
		free_env(env);
	if (branch)
		free_tree(branch);
	rl_clear_history();
	exit(code);
}

int	exit_built_in(t_branch *branch)
{
	t_cmd	*cmd;
	int		code;

	cmd = branch->elmnt;
	ft_dprintf(2, "exit\n");
	if (!cmd->args[1])
		free_and_exit(cmd->env->err_no, branch, cmd->env);
	if (!check_exit_first_arg(cmd->args[1]))
	{
		ft_dprintf(2, EXIT_NON_NUM_ARG, cmd->args[1]);
		free_and_exit(2, branch, cmd->env);
	}
	if (cmd->args[1] && cmd->args[2])
		return ((ft_dprintf(2, EXIT_TOO_MANY_ARG) > 0));
	code = ft_atoi(cmd->args[1]) % 256;
	free_and_exit(code, branch, cmd->env);
	return (1);
}
