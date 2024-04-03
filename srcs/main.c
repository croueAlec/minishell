/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:13:47 by acroue            #+#    #+#             */
/*   Updated: 2024/04/02 11:11:05 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_branch	*first_branch;
	t_branch	*tree;
	t_cmd		*thecmd;

	(void) ac;
	(void) av;
	tree = parsing(env);
	// printf("j ai un arbre\n");
	// printf("tree %p\n", tree);
	thecmd = tree->elmnt;
	first_branch = tree;
	// while (tree)
	// {
	// 	printf("BRANCH TYPE = %i\n", tree->type);
	// 	printf("CMD PATH = %s\n", thecmd->cmd_path);
	// 	printf("CMD ARGS\n");
	// 	ft_printstrtab(thecmd->args);
	// 	printf("CMD REDIRECTIONS\n");
	// 	int i = 0;
	// 	while (thecmd->tree[i])
	// 	{
	// 		if (thecmd->tree[i]->type == 2)
	// 			printf("redir = INFILE\n");
	// 		else if (thecmd->tree[i]->type == 3)
	// 			printf("redir = OUTFILE\n");
	// 		i++;
	// 	}
	// 	printf("===============\n===============\n");
	// 	printf("%p\n", thecmd->next_cmd);
	// 	tree = thecmd->next_cmd;
	// 	if (tree)
	// 		thecmd = tree->elmnt;
	// 	// printf("d\n%p\n", tree->elmnt);
	// }
	// printf("je le print\n");
	execute_tree(first_branch, env);
	// free_tree(first_branch);
	return (0);
}
