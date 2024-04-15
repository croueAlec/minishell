/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:17:11 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 12:47:09 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the edge cases such as commands not found, unset 
 * paths or redirections only.
 * 
 * @param branch The current CMD Branch.
 * @param cmd_number The current command number inside the pipeline.
 * @return t_cmd* Returns a pointer to the current command if it has not been 
 * executed, or the next if it has.
 */
t_cmd	*basic_check(t_branch *branch)
{
	t_branch	*old_curr_branch;
	t_cmd		*cmd;

	cmd = branch->elmnt;
	old_curr_branch = NULL;
	while (cmd)
	{
		if (cmd && cmd->cmd_path)
			return (cmd);
		if (cmd && cmd->next_cmd)
			old_curr_branch = cmd->next_cmd;
		if (!cmd->cmd_path && !cmd->args[0])
			cmd = open_close_redir(branch, old_curr_branch);
		else if (!cmd->cmd_path && is_built_in(branch))
			return (cmd);
		else
			cmd = handle_cmd_not_found(branch);
		branch->elmnt = cmd;
		old_curr_branch = NULL;
	}
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
	if (!isatty(infile))
		close(infile);
	dup2(outfile, STDOUT_FILENO);
	if (!isatty(outfile))
		close(outfile);
	execve(cmd->cmd_path, cmd->args, env);
	perror(cmd->args[0]);
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
}

pid_t	fork_cmd(t_branch *branch, char **env, int pipefd[2], int tmp_in)
{
	pid_t	pid;
	int		infile;
	int		outfile;

	pid = fork();
	if (pid == 0)
	{
		if (tmp_in != pipefd[0])
			close(pipefd[0]);
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
	if (tmp_in > 0 && !isatty(tmp_in))
		close(tmp_in);
	track_and_close_hd_fd(branch);
	free_curr_branch(branch);
	return (pid);
}

/**
 * @brief Handles pipes and redirections before calling execute_cmd();
 * 
 * @param branch A pointer to the Branch Command Structure
 * @param env The Minishell's local environment
 */
pid_t	execute_tree(t_branch *branch, t_env *env, size_t cmd_number)
{
	t_branch	*next_branch;
	int			tmp_outfile;
	int			pipefd[2];
	t_cmd		*cmd;
	pid_t		last_pid;

	last_pid = UNDEFINED_FD;
	define_execution_fd(&pipefd[0], &pipefd[1], &tmp_outfile);
	while (branch)
	{
		cmd = basic_check(branch);
		if (!cmd || (cmd->next_cmd && (open_pipe(branch, pipefd, tmp_outfile))))
			break ;
		next_branch = cmd->next_cmd;
		if (!cmd->cmd_path)
			last_pid = fork_built_ins(pipefd, branch, &cmd_number);
		else
			last_pid = fork_cmd(branch, env->env_tab, pipefd, tmp_outfile);
		tmp_outfile = pipefd[0];
		if (pipefd[1] >= 0 && !isatty(pipefd[1]))
			(close(pipefd[1]), pipefd[1] = UNDEFINED_FD);
		branch = next_branch;
	}
	return (free(branch), last_pid);
}
