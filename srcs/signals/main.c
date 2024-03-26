/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:36:40 by acroue            #+#    #+#             */
/*   Updated: 2024/03/26 11:46:00 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_signals.h"

int	g_global;

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

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	struct sigaction	sa2;
	g_global = 0;

	sa.sa_handler = handle_ctrl_c;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa2.sa_handler = handle_c;
	sa2.sa_flags = 0;
	sigemptyset(&sa2.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (g_global == 0 || g_global == 1)
	{
		if (g_global == 1)
			sigaction(SIGINT, &sa2, NULL);
	}
	return ((void)argc, (void)argv, 0);
}
