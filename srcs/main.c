/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:47 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 15:23:00 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int ac, char **av, char **default_env)
{
	t_branch	*tree;
	pid_t		last_pid;
	t_env		*env_struct;

	(void) ac;
	(void) av;
	env_struct = make_env(default_env);
	while (1)
	{
		tree = parsing(env_struct);
		last_pid = execute_tree(tree, env_struct, 0);
		if (last_pid != UNDEFINED_FD)
			wait_children(last_pid);
	}
	rl_clear_history();
	return (0);
}
