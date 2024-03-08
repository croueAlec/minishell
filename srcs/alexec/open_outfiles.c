/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:00 by acroue            #+#    #+#             */
/*   Updated: 2024/03/08 18:11:22 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a branch containing an Outfile Struct
 * 
 * @param branch The branch pointer
 */
void	free_outfile_branch(t_branch *branch)
{
	t_infile	*outfile;

	outfile = branch->elmnt;
	free(outfile->path);
	outfile->path = NULL;
	free(outfile);
	free(branch);
}

/**
 * @brief Opens the outfile in Append or Truncate mode.
 * In case of insufficient permissions an error message is printed
 * 
 * @param branch a branch containing an Outfile Struct
 * @param outfile_fd a previously opened outfile to be closed or UNDEFINED_FD 
 * (-2)
 * @return int The opened outfile_fd in case of success or E_FD (-1) in case of 
 * error
 */
int	open_outfile(t_branch *branch, int outfile_fd)
{
	t_outfile	*outfile;
	int	open_flags;

	outfile = branch->elmnt;
	if (outfile_fd != UNDEFINED_FD)
		close(outfile_fd);
	open_flags = O_WRONLY | O_APPEND | O_CREAT;
	if (outfile->type == OT_TRUNC)
		open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	printf("Je suis un redirect de outfile\n");
	if (outfile->type == OT_TRUNC || outfile->type == OT_APPEND)
	{
		outfile_fd = open(outfile->path, open_flags, 0644);
		if (outfile_fd < 0)
			return (perror(outfile->path), free_outfile_branch(branch), E_FD);
	}
	return (free_outfile_branch(branch), outfile_fd);
}
