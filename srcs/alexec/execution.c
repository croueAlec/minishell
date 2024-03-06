/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 15:24:17 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(cmd->cmd_path);
	free(cmd);
}

/**
 * @brief Handles pipes and redirections before calling execute_cmd();
 * 
 * @param cmd A pointer to the command structure
 * @param env The Minishell's local environment
 */
void	execute_tree(t_branch *branch, char **env)
{
	int		infile;
	int		outfile;
	t_cmd	*cmd;

	cmd = branch->elmnt;
	if (access(cmd->cmd_path, X_OK))
		(free(cmd->cmd_path), cmd->cmd_path = NULL);
	if (!cmd->cmd_path)
		return (cmd_error(branch, "Cmd error thus free\n"));
	infile = open_infiles(cmd->tree);
	outfile = open_outfiles(cmd->tree);
	if (outfile == E_FD || infile == E_FD)
		return (redirection_error(branch, "Redirection error thus free\n"));
	printf("infile : %d\noutfile : %d\n", infile, outfile);
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execute_cmd(cmd, env);
	free(branch);
}
