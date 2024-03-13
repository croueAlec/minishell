/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/03/13 20:17:02 by acroue           ###   ########.fr       */
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
 * @brief Opens pipe. In case of error, frees the current command and passes to
 *  the next.
 * 
 * @param branch The address of the Branch Pointer.
 * @param pipefd The pipe to open.
 * @param tmp_outfile The previously opened pipe. Closes on error.
 * @return 0 on error, 1 when successful
 */
int	open_pipe(t_branch **branch, int pipefd[2], int tmp_outfile)
{
	t_branch	*curr_branch;
	t_branch	*next_branch;
	t_cmd		*cmd;

	if (pipe(pipefd) > 0)
		return (1);
	if (tmp_outfile >= 0)
		close(tmp_outfile);
	perror(pipe);
	curr_branch = *branch;
	cmd = curr_branch->elmnt;
	if (cmd->next_cmd)
	{
		next_branch = cmd->next_cmd;
	}
	*branch = next_branch;
	cmd->next_cmd = NULL;
	free_tree(curr_branch);
	return (0);
}

t_cmd	*return_next_cmd()
{
	;
}

/**
 * @brief Executes the edge cases such as built-ins, commands not found, unset 
 * paths or redirections only.
 * 
 * @param branch The current CMD Branch.
 * @param cmd_number The current command number inside the pipeline.
 * @return t_cmd* Returns a pointer to the cmd to execute
 */
t_cmd	*basic_check(t_branch *branch, int *cmd_number)
{
	t_cmd	*cmd;
	int		builtin_type;

	cmd = branch->elmnt;
	if (!cmd->cmd_path && !cmd->args)
		return (open_close_redir(branch));
	if (!cmd->cmd_path && !handle_builtins(branch, cmd_number))
		// return_next_cmd();
		
	return (cmd);
}

/**
 * @brief Handles pipes and redirections before calling execute_cmd();
 * 
 * @param branch A pointer to the Branch Command Structure
 * @param env The Minishell's local environment
 */
void	execute_tree(t_branch *branch, char **env)
{
	size_t	cmd_number;
	int		tmp_outfile;
	int		pipefd[2] = {UNDEFINED_FD, UNDEFINED_FD};
	t_cmd	*cmd;

	cmd_number = 0;
	tmp_outfile = UNDEFINED_FD;
	while (1)
	{
		cmd = basic_check(branch, &cmd_number);
		free(branch);
		if (cmd->next_cmd && (open_pipe(&branch, pipefd, tmp_outfile) < 1))
			continue ; // je dois changer open pipe
		branch = cmd->next_cmd;
	}
}
		// if (cmd->next_cmd && (open_pipe(&branch, pipefd, tmp_outfile) < 1))
		// 	continue ;
		// open_redirections(pipefd[0], pipefd[1], branch); // j'en etais ici
		// if (pipefd[0] != E_FD && pipefd[1] != E_FD)
		// 	execute_cmd(NULL, NULL);
		// tmp_outfile = pipefd[1]; // utiliser isatty 
		// branch = cmd->next_cmd;
		// cmd = branch->elmnt;
		// if (!cmd->next_cmd)
		// 	break ;
// 
// 
	// printf("infile : %d\noutfile : %d\n", infile, outfile);
	// dup2(infile, STDIN_FILENO);
	// close(infile);
	// dup2(outfile, STDOUT_FILENO);
	// close(outfile);
	// execute_cmd(cmd, env);
	// free(branch);
