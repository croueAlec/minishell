/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:36:59 by acroue            #+#    #+#             */
/*   Updated: 2024/03/20 13:52:03 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function only gets called if there are only redirections and no 
 * command. It will open infiles and outfiles in order then close them.
 * 
 * @param branch The current CMD Branch which has cmd_path and args to NULL.
 * @return *t_cmd A pointer to the next cmd or NULL if there is none.
 */
t_cmd	*open_close_redir(t_branch *branch)
{
	t_branch	*next_branch;
	t_cmd		*cmd;
	int			infile;
	int			outfile;

	cmd = branch->elmnt;
	next_branch = cmd->next_cmd;
	infile = UNDEFINED_FD;
	outfile = UNDEFINED_FD;
	open_redirections(&infile, &outfile, branch);
	if (infile >= 0)
		close(infile);
	if (outfile >= 0)
		close(outfile);
	return (next_branch->elmnt); // soucis ici
}

void	open_redirections(int *infile, int *outfile, t_branch *branch)
{
	t_cmd	*cmd;
	size_t	i;

	i = 0;
	cmd = branch->elmnt;
	// if (access(cmd->cmd_path, X_OK))
	// 	(free(cmd->cmd_path), cmd->cmd_path = NULL);
	// if (!cmd->cmd_path)
	// 	return (cmd_error(branch, "Cmd error thus free\n"));
	while (cmd->tree && cmd->tree[i] != NULL)
	{
		if (cmd->tree[i]->type == T_INFILE)
			*infile = open_infile(cmd->tree[i], *infile);
		else if (cmd->tree[i]->type == T_OUTFILE)
			*outfile = open_outfile(cmd->tree[i], *outfile);
		else
			printf("hmm what kind of branch is %d ?\n", cmd->tree[i]->type);
		if (*outfile == E_FD || *infile == E_FD)
			return (redirection_error(branch, i));
		i++;
	}
}
/* this function should free everything when it encounters an error */
