/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:23 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 10:43:08 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_branch	*define_test_infile(char *path)
{
	t_branch	*branch;
	t_infile	*infile;

	branch = ft_calloc(sizeof(t_branch), 1); // free dans open_infiles()
	infile = ft_calloc(sizeof(t_infile), 1);// free dans infile_leaves()
	branch->type = T_INFILE;
	branch->elmnt = infile;
	infile->path = ft_strdup(path); // free dans infile_leaves()
	infile->type = IT_RDONLY;
	return (branch);
}

static t_branch	*define_test_outifle(char *path, t_out_type type)
{
	t_branch	*branch;
	t_outfile	*outfile;

	branch = ft_calloc(sizeof(t_branch), 1); // free dans open_outfiles()
	outfile = ft_calloc(sizeof(t_outfile), 1);// free dans outfile_leaves()
	branch->type = T_OUTFILE;
	branch->elmnt = outfile;
	outfile->path = ft_strdup(path); // free dans outfile_leaves()
	outfile->type = type;
	return (branch);
}

static t_branch	*define_test_cmd(t_branch *branch)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd_path = "/usr/bin/ls";
	cmd->args = ft_calloc(sizeof(char *), 3);
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = ft_strdup("-n");
	cmd->args[2] = NULL; // tout ca free dans execute_cmd
	branch->elmnt = cmd;
	branch->type = T_CMD;
	cmd->tree = ft_calloc(sizeof(t_branch *), 6);
	cmd->tree[0] = define_test_infile("Makefile");
	cmd->tree[1] = define_test_infile(".gitignore");
	cmd->tree[2] = define_test_outifle("outone", OT_APPEND);
	cmd->tree[3] = define_test_outifle("outtwo", OT_TRUNC);
	cmd->tree[4] = NULL;
	return (branch);
}

int	main(int argc, char *argv[], char **env)
{
	t_branch	*branch;

	branch = ft_calloc(sizeof(t_branch), 1);
	branch = define_test_cmd(branch);
	execute_tree(branch->elmnt, env);
	free(branch);
	(void)argc;
	(void)argv;
	return (0);
}
