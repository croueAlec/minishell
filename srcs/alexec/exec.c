/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 10:00:37 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exec(void)
{
	printf("this is the exec\n");
}

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	execute_cmd(t_cmd *cmd, char **env)
{
	pid_t	pid;
	printf("Je suis une commande\n");
	pid = fork();
	if (pid == 0)
		execve(cmd->cmd_path, cmd->args, env);
	// free(cmd->args[0]);
	// free(cmd->args[1]);
	// free(cmd->args);
	free_tab((void **)cmd->args);
	free(cmd->tree);
	free(cmd);
}

void	execute_tree(t_cmd *cmd, char **env)
{
	int	infile;
	int	outfile;

	infile = open_infiles(cmd->tree);
	if (infile == E_FD)
		return ;
	outfile = open_outfiles(cmd->tree);
	if (outfile == E_FD)
		return ;
	printf("infile : %d\noutfile : %d\n", infile, outfile);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(cmd, env);
}

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

int main(int argc, char *argv[], char **env)
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
