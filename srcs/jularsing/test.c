/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:41:19 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/13 10:48:05 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;

	char *str = readline("LINE = ");
	char **split = quotes_split(str, '|');
	printf("QUOTES SPLIT UN\n");
	ft_printstrtab(split);
	printf("===========================\n");
	int i = 0;
	ssize_t index = 0;
	char *cmd;
	while (split[i] != 0)
	{
		cmd = dup_expanded_char(index, str,  env);
		index = fetch_cmd_index(split[i]);
		printf("cmd index = %zd\n", index);
		printf ("cmd expanded is %s\n", cmd);
		printf("cmd is builtin = %d\n", isbuiltin(cmd));
		printf("cmd path = %s\n", fetch_cmd_path(cmd, env));
		
	}
	
	return (0);
}
