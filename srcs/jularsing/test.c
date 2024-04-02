/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:41:19 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/30 11:43:39 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	t_branch	*tree;
// 	t_cmd		*thecmd;

// 	(void) ac;
// 	(void) av;
// 	tree = parsing(env);
// 	printf("j ai un arbre\n");
// 	printf("tree %p\n", tree);
// 	thecmd = tree->elmnt;
// 	while (tree)
// 	{
// 		printf("BRANCH TYPE = %i\n", tree->type);
// 		printf("CMD PATH = %s\n", thecmd->cmd_path);
// 		printf("CMD ARGS\n");
// 		ft_printstrtab(thecmd->args);
// 		printf("CMD REDIRECTIONS\n");
// 		int i = 0;
// 		while (thecmd->tree[i])
// 		{
// 			printf("REDIRECTION = %s\n", (char *) thecmd->tree[i]->elmnt);
// 			i++;
// 		}
// 		printf("===============\n===============\n");
// 		printf("%p\n", thecmd->next_cmd);
// 		tree = thecmd->next_cmd;
// 		printf("d\n%p\n", tree->elmnt);
// 		if (tree)
// 			thecmd = tree->elmnt;
// 	}
// 	printf("je le print\n");
// 	free_tree(tree);
// 	return (0);
// }
