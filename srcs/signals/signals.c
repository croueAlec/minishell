/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:51:34 by acroue            #+#    #+#             */
/*   Updated: 2024/04/16 14:14:31 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle_c_hd(int signum)
{
	g_global = signum;
	close(STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
}

void	sig_handle_c(int signum)
{
	g_global = signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Defines the behavior of signals at the beginning of the program
 */
void	set_signals_default(t_env *env)
{
	define_sig(SIGINT, &sig_handle_c, env);
	define_sig(SIGQUIT, SIG_IGN, env);
}

int	define_sig(int signum, void(*fun_ptr)(int), t_env *env)
{
	struct sigaction	sa;

	sa.sa_handler = fun_ptr;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, NULL) < 0)
	{
		env->err_no = errno;
		perror("sigaction");
		return (-1);
	}
	env->err_no = 0;
	return (0);
}

// int	main(int argc, char *argv[])
// {
// 	g_global = 0;
// 	define_sig(SIGINT, &handle_ctrl_c);
// 	define_sig(SIGQUIT, SIG_IGN);
// 	while (g_global == 0 || g_global == 1)
// 	{
// 		if (g_global == 1)
// 			define_sig(SIGINT, &handle_c);
// 	}
// 	return ((void)argc, (void)argv, 0);
// }
