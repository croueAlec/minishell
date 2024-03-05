/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 18:28:43 by acroue           ###   ########.fr       */
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

/**
 * @brief Executes the command once pipes and redirects have been done
 * 
 * @param cmd A pointer to the Command structure
 * @param env The Minishell's local environment
 */
void	execute_cmd(t_cmd *cmd, char **env)
{
	pid_t	pid;

	printf("Je suis une commande\n");
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->cmd_path, cmd->args, env) == -1)
		{
			perror("Command failed, why ??");
		}
	}
	free_tab((void **)cmd->args);
	free(cmd->tree);
	free(cmd);
}

/**
 * @brief Handles pipes and redirections before calling execute_cmd();
 * 
 * @param cmd A pointer to the command structure
 * @param env The Minishell's local environment
 */
void	execute_tree(t_cmd *cmd, char **env)
{
	int	infile;
	int	outfile;

	if (access(cmd->cmd_path, X_OK))
		cmd->cmd_path = NULL;
	if (!cmd->cmd_path)
		return ((void)ft_dprintf(2, "%s : command not found\n", cmd->args[0]));
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
