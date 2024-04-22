/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:47 by acroue            #+#    #+#             */
/*   Updated: 2024/04/22 13:28:11 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global = 0;

static void	sig_handle_c(int signum)
{
	g_global = signum;
	ft_putchar_fd('\n', 1);
}

static int	wait_children(int pid, t_env *env)
{
	int	wait_status;
	int	error_status;

	define_sig(SIGINT, &sig_handle_c, env);
	while (errno != ECHILD)
		if (wait(&wait_status) == pid && WIFEXITED(wait_status))
			error_status = WEXITSTATUS(wait_status);
	if (pid == -1)
		return (127);
	return (error_status);
}

static int	skip_cmd_hd_sigint(t_branch *tree, t_env *env)
{
	env->err_no = 130;
	free_tree(tree);
	g_global = 0;
	return (1);
}

int	main(int ac, char **av, char **default_env)
{
	t_branch	*tree;
	pid_t		last_pid;
	t_env		*env_struct;

	(void) ac, (void) av;
	if (!isatty(0))
		return ((void)ft_dprintf(2, YOU_CANT_DO_THAT), 1);
	env_struct = make_env(default_env);
	while (1)
	{
		set_signals_default(env_struct);
		tree = parsing(env_struct);
		if (g_global == SIGINT_HD && skip_cmd_hd_sigint(tree, env_struct))
			continue ;
		last_pid = execute_tree(tree, env_struct, 0);
		if (last_pid != UNDEFINED_FD)
			env_struct->err_no = wait_children(last_pid, env_struct);
	}
	rl_clear_history();
	return (0);
}
