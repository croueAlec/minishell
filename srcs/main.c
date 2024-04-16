/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:47 by acroue            #+#    #+#             */
/*   Updated: 2024/04/16 14:12:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

int	wait_children(int pid)
{
	int	wait_status;
	int	error_status;

	while (errno != ECHILD)
		if (wait(&wait_status) == pid && WIFEXITED(wait_status))
			error_status = WEXITSTATUS(wait_status);
	if (pid == -1)
		return (127);
	return (error_status);
}

static int	skip_cmd_hd_sigint(t_branch *tree)
{
	free_tree(tree);
	g_global = 0;
	return (1);
}

int	main(int ac, char **av, char **default_env)
{
	t_branch	*tree;
	pid_t		last_pid;
	t_env		*env_struct;

	(void) ac;
	(void) av;
	env_struct = make_env(default_env);
	set_signals_default(env_struct);
	while (1)
	{
		if (g_global == SIGINT)
			env_struct->err_no = 130;
		g_global = 0;
		tree = parsing(env_struct);
		if (g_global == SIGINT && skip_cmd_hd_sigint(tree))
			continue ;
		last_pid = execute_tree(tree, env_struct, 0);
		if (last_pid != UNDEFINED_FD)
			wait_children(last_pid);
	}
	rl_clear_history();
	return (0);
}
