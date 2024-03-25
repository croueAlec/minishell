/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:41:19 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/25 10:08:22 by jblaye           ###   ########.fr       */
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
		t_pars_list **parsing = extract_input_data(split_again);
		t_pars_list *first_arg = parsing[0];
		t_pars_list *first_file = parsing[1];
		while (first_arg != NULL)
		{
			printf("ARG = %s\n", first_arg->s);
			first_arg = first_arg->next;
		}
		while (first_file != NULL)
		{
			printf("FILE = %s\n", first_file->s);
			first_file = first_file->next;
		}
		i++;
	}
		// char **pipe_split = quote_expansion_split(result, ' ');
	// 	printf("PIPE SPLIT\n");
	// 	ft_printstrtab(pipe_split);
	// 	printf("---------------------------\n");
	// 	index = fetch_cmd_index(pipe_split);
	// 	printf("cmd index = %zd\n", index);
	// 	// char *cmd = dup_expanded_char(0, pipe_split[i], env);
	// 	// printf ("cmd expanded is %s\n", cmd);
	// 	// printf("cmd is builtin = %d\n", isbuiltin(cmd));
	// 	// printf("cmd path = %s\n", fetch_cmd_path(cmd, env));
	// 	printf("===========================\n===========================\n");
	// i++;
	// }
	return (0);
}
