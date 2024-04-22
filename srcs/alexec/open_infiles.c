/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:15:40 by acroue            #+#    #+#             */
/*   Updated: 2024/04/22 12:34:59 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a branch containing an Infile Struct
 * 
 * @param branch The branch pointer
 */
void	free_infile_branch(t_branch *branch)
{
	t_infile	*infile;

	infile = branch->elmnt;
	if (infile->path)
		(free(infile->path), infile->path = NULL);
	(free(infile), infile = NULL);
	(free(branch), branch = NULL);
}

int	open_here_doc(t_branch *branch)
{
	t_infile	*infile;
	int			fd;

	infile = branch->elmnt;
	fd = infile->fd;
	return (free_infile_branch(branch), fd);
}

/**
 * @brief Opens infile (or here_doc) and makes sure it exists. In case of 
 * insufficient permissions an error message is printed. 
 * Closes previous infiles.
 * @param branch a branch containing an Infile Struct
 * @param infile_fd a previously opened infile to be closed or UNDEFINED_FD (-2)
 * @return int The opened infile_fd in case of success or E_FD (-1) in case of
 * error
 */
int	open_infile(t_branch *branch, int infile_fd)
{
	t_infile	*infile;

	infile = branch->elmnt;
	if (infile_fd != UNDEFINED_FD)
		close(infile_fd);
	if (infile->type == IT_HERE_DOC)
		return (open_here_doc(branch));
	if (infile->type == IT_RDONLY)
	{
		infile_fd = open(infile->path, O_RDONLY);
		if (infile_fd < 0)
			return ((void)ft_dprintf(2, "tacOS: "), \
			perror(infile->path), free_infile_branch(branch), E_FD);
	}
	return (free_infile_branch(branch), infile_fd);
}
