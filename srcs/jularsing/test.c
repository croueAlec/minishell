/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:41:19 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/26 11:39:58 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	//(void) env;
	
	// char *str = "ok";
	// while (str[0] != 'z')
	// {
	char *str = readline("ENTER INPUT> ");
	// 	printf("VALID ? %d\n", no_pipe_syntax_error(str));
	// }
	char **split = quotes_split(str, '|');
	printf("QUOTES SPLIT UN\n");
	ft_printstrtab(split);
	printf("===========================\n===========================\n");
	int i = 0;
	while (split[i] != 0)
	{
		char *result = str_expand_var(split[i], env);
		printf("STR APRES EXPANSION = %s\n", result);
		char **split_again = quotes_split(result, ' ');
		ft_printstrtab(split_again);
		printf("===========================\n");
		// t_pars_list *first_arg = parsing[0];
		// t_pars_list *first_file = parsing[1];
		//char **args_tab = generate_args_tab(&first_arg);
		// t_branch **redir = generate_redir_tab(&first_file, 0);
		t_cmd *cmd = new_cmd(split_again, -1, env);
		int j = 0;
		while (cmd->args[j] != 0)
		{
			printf("ARG = |%s|\n", cmd->args[j]);
			j++;
		}
		// j = 0;
		// while (redir[j] != 0)
		// {
		// 	if (redir[j]->type == T_OUTFILE)
		// 	{
		// 		t_outfile *out = redir[j]->elmnt;
		// 		printf("FILE = %s\n", out->path);
		// 	}
		// 	if (redir[j]->type == T_INFILE)
		// 	{
		// 		t_infile *in = redir[j]->elmnt;
		// 		printf("FILE = %s\n", in->path);
		// 	}
		// 	j++;
		// }
		printf("===========================\n===========================\n");
		i++;
	}
	return (0);
}
