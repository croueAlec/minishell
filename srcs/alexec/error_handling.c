/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:18:21 by acroue            #+#    #+#             */
/*   Updated: 2024/04/23 11:47:25 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_branch	*free_curr_branch(t_branch *branch)
{
	t_branch	*next_branch;
	t_cmd		*cmd;

	cmd = branch->elmnt;
	next_branch = cmd->next_cmd;
	cmd->next_cmd = NULL;
	free_tree(branch);
	return (next_branch);
}

void	cmd_error(t_branch *branch, char *err_msg)
{
	ft_dprintf(2, "%s", err_msg);
	free_curr_branch(branch);
}

/**
 * @brief In case of a redirection error (invalid permissions, missing file...) 
 * this function frees the parent Command Branch and all of it's contents
 * 
 * @param branch The branch command structure to be freed
 * @param tree_index The index of the failing infile from whence to free
 * @param err_msg The error message to display when the function is called
 */
void	redirection_error(t_branch *branch, size_t tree_index)
{
	t_cmd	*cmd;

	cmd = branch->elmnt;
	while (cmd->tree && cmd->tree[tree_index] != NULL)
	{
		if (cmd->tree[tree_index]->type == T_INFILE)
		{
			free_infile_branch(cmd->tree[tree_index]);
			cmd->tree[tree_index] = NULL;
		}
		else if (cmd->tree[tree_index]->type == T_OUTFILE)
		{
			free_outfile_branch(cmd->tree[tree_index]);
			cmd->tree[tree_index] = NULL;
		}
		tree_index++;
	}
}

/**
 * @brief If the infile and outfile descriptors opened incorrectly they get clo
 * sed and 0 is returned.
 * @return int 0 if infile or outfile was incorrectly opened, or 1.
 */
int	did_file_open_correctly(int infile, int outfile)
{
	if (infile == E_FD || outfile == E_FD)
	{
		if (infile >= 0)
			close(infile);
		if (outfile >= 0)
			close(outfile);
		return (0);
	}
	return (1);
}

/**
 * @brief Exits forks when commands fail with execve.
 * 
 * @param err_no Exit's return code.
 */
void	on_cmd_error(pid_t pid, t_branch *branch)
{
	t_cmd	*cmd;

	cmd = branch->elmnt;
	if (pid == 0)
	{
		free_env(cmd->env);
		free_tree(branch);
		exit(126);
	}
}
