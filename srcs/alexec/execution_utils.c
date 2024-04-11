/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:31:22 by acroue            #+#    #+#             */
/*   Updated: 2024/04/11 17:34:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns 1 if cmd is a path (contains a /). Edge case to print the 
 * correct command not found message.
 */
int	is_cmd_path(char *cmd, char ch)
{
	size_t	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Returns 1 if path is unset or empty. Edge case to print the correct 
 * command not found message.
 */
int	is_path_unset(t_env *env)
{
	size_t	i;

	i = 0;
	while (env && env->env_tab[i])
	{
		if (ft_strncmp("PATH=", env->env_tab[i], 5) == 0)
			break ;
		i++;
	}
	if (!env || !env->env_tab[i] || !ft_strncmp("PATH=", env->env_tab[i], 6))
		return (1);
	return (0);
}

/**
 * @brief Sets the values of the FDs to UNDEFINED_FD (-2).
 */
void	define_execution_fd(int *fd_one, int *fd_two, int *fd_three)
{
	if (fd_one)
		*fd_one = UNDEFINED_FD;
	if (fd_two)
		*fd_two = UNDEFINED_FD;
	if (fd_three)
		*fd_three = UNDEFINED_FD;
}

/**
 * @brief Returns the next cmd when the previous one is invalid.
 */
t_cmd	*return_next_cmd(t_branch *branch)
{
	t_branch	*next_branch;
	t_cmd		*curr_cmd;
	t_cmd		*next_cmd;

	curr_cmd = branch->elmnt;
	next_branch = curr_cmd->next_cmd;
	if (!next_branch)
		return (NULL);
	next_cmd = next_branch->elmnt;
	branch->elmnt = next_cmd;
	free_file_tree(curr_cmd->tree);
	free_cmd(curr_cmd);
	return (next_cmd);
}
