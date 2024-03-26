/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:36:40 by acroue            #+#    #+#             */
/*   Updated: 2024/03/26 20:01:23 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "minishell.h"
#include "minishell_signals.h"

void	handle_ctrl_c(int signum)
{
	printf("This is a signal %d\n", signum);
	g_global = 1;
}

void	handle_c(int signum)
{
	printf("This is the other signal %d\n", signum);
	g_global = signum;
}

void	define_sig(int signum, void(*fun_ptr)(int))
{
	struct sigaction	sa;

	sa.sa_handler = fun_ptr;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

int	main(int argc, char *argv[])
{
	g_global = 0;
	define_sig(SIGINT, &handle_ctrl_c);
	define_sig(SIGQUIT, SIG_IGN);
	while (g_global == 0 || g_global == 1)
	{
		if (g_global == 1)
			define_sig(SIGINT, &handle_c);
	}
	return ((void)argc, (void)argv, 0);
}
