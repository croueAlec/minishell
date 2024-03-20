/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/03/20 18:51:43 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /**
//  * @brief Executes the command once pipes and redirects have been done
//  * 
//  * @param cmd A pointer to the Command structure
//  * @param env The Minishell's local environment
//  */
// void	execute_cmd(t_cmd *cmd, char **env)
// {
// 	pid_t	pid;

// 	printf("Je suis une commande\n");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd->cmd_path, cmd->args, env) == -1)
// 		{
// 			perror("Command failed, why ??");
// 		}
// 	}
// 	free_tab((void **)cmd->args);
// 	free(cmd->tree);
// 	free(cmd->cmd_path);
// 	free(cmd);
// }

/**
 * @brief Opens pipe. In case of error, frees the current command and passes to
 *  the next.
 * 
 * @param branch The address of the Branch Pointer.
 * @param pipefd The pipe to open.
 * @param tmp_outfile The previously opened pipe. Closes on error.
 * @return 0 on error, 1 when successful
 */
int	open_pipe(t_branch *branch, int pipefd[2], int tmp_outfile)
{
	if (pipe(pipefd) == 0)
		return (0);
	if (tmp_outfile >= 0)
		close(tmp_outfile);
	return (free_tree(branch), perror("pipe"), 1);
}

/**
 * @brief Executes the edge cases such as built-ins, commands not found, unset 
 * paths or redirections only.
 * 
 * @param branch The current CMD Branch.
 * @param cmd_number The current command number inside the pipeline.
 * @return t_cmd* Returns a pointer to the current command if it has not been 
 * executed, or the next if it has.
 */
t_cmd	*basic_check(t_branch *branch, size_t *cmd_number)
{
	t_cmd	*cmd;
	// int		is_directory;
	// int		builtin_type;

	(void)cmd_number;
	cmd = branch->elmnt;
	if (!cmd->cmd_path && !cmd->args)
		return (open_close_redir(branch));
	// if (!cmd->cmd_path && !handle_builtins(branch, cmd_number))
		// return_next_cmd();
	// is_directory = (ft_strncmp(ft_strchr(cmd->cmd_path, '/'), "/", 1) == 0);
	// if (env[find_env_index("PATH")] == NULL || is_directory)
	// {
	// 	errno = 127;
	// 	perror(cmd->args[0]);
	// 	return_next_cmd();
	// }
	// else if (!is_directory)
	// {
	// 	errno = 2;
	// 	perror(cmd->args[0]);
	// 	return_next_cmd();
	// }
	return (cmd);
}

void	execute_cmd(t_branch *branch, char **env, int infile, int outfile)
{
	t_cmd	*cmd;

	cmd = branch->elmnt;
	if (infile == UNDEFINED_FD)
		infile = STDIN_FILENO;
	if (outfile == UNDEFINED_FD)
		outfile = STDOUT_FILENO;
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	execve(cmd->cmd_path, cmd->args, env);
	perror(cmd->args[0]);
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
}

void	fork_cmd(t_branch *branch, char **env, int pipefd[2], int tmp_in)
{
	pid_t	pid;
	int		infile;
	int		outfile;

	pid = fork();
	if (pid == 0)
	{
		infile = tmp_in;
		outfile = pipefd[1];
		open_redirections(&infile, &outfile, branch);
		if (did_file_open_correctly(infile, outfile))
			execute_cmd(branch, env, infile, outfile);
		if (infile >= 0)
			close(infile);
		if (outfile >= 0)
			close(outfile);
	}
	if (tmp_in > 0)
		close(tmp_in);
	free_curr_branch(branch);
	(void)env;
	(void)pipefd; //gerer le pipefd
}

/**
 * @brief Handles pipes and redirections before calling execute_cmd();
 * 
 * @param branch A pointer to the Branch Command Structure
 * @param env The Minishell's local environment
 */
void	execute_tree(t_branch *branch, char **env)
{
	t_branch	*next_branch;
	size_t		cmd_number;
	int			tmp_outfile;
	int			pipefd[2] = {UNDEFINED_FD, UNDEFINED_FD};
	t_cmd		*cmd;

	cmd_number = 0;
	tmp_outfile = UNDEFINED_FD;
	while (branch)
	{
		cmd = basic_check(branch, &cmd_number);
		if (cmd->next_cmd && (open_pipe(branch, pipefd, tmp_outfile)))
			break ; // exit en cas de fail pipe
		next_branch = cmd->next_cmd;
		fork_cmd(branch, env, pipefd, tmp_outfile);
		tmp_outfile = pipefd[0];
		if (pipefd[1] >= 0 && !isatty(pipefd[1]))
			close(pipefd[1]);
		pipefd[1] = UNDEFINED_FD;
		branch = next_branch;
		cmd_number++;
	}
}
