/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:00 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 10:24:35 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the contents of the Outfile Struct. The branches themselves get 
 * freed in open_outfiles();
 * 
 * @param outfile The Outfile Struct
 */
void	free_outfile_leaves(t_outfile *outfile)
{
	free(outfile->path);
	outfile->path = NULL;
	free(outfile);
}

/**
 * @brief Opens the outfile in Append or Truncate mode.
 * Prints an error message in case of error
 * 
 * @param fd The file descriptor of the previously opened outfile, or 
 * UNDEFINED_FD if this is the first file
 * @param outfile The Outfile Struct indicating what to open and how
 * @return int The file descriptor of the opened outfile or E_FD in case of 
 * error
 */
static int	redirect_outfile(int fd, t_outfile *outfile)
{
	int	open_flags;

	open_flags = O_WRONLY | O_APPEND | O_CREAT;
	if (outfile->type == OT_TRUNC)
		open_flags = O_WRONLY | O_TRUNC | O_CREAT;
	if (fd >= 0)
		close(fd);
	printf("Je suis un redirect de outfile\n");
	if (outfile->type == OT_TRUNC || outfile->type == OT_APPEND)
	{
		fd = open(outfile->path, open_flags, 0644);
		if (fd < 0)
			return (perror(outfile->path), free_outfile_leaves(outfile), E_FD);
	}
	return (free_outfile_leaves(outfile), fd);
}

/**
 * @brief Opens outfiles and makes sur they have the right permissions if they
 * exist or creates them if they don't. Frees all the branches after their 
 * contents have been freed in free_*_leaves();
 * 
 * @param tree An array of branches from the AST, parameters of the CMD Struct
 * @return int The last opened outfile in case of success or E_FD (-1) in case 
 * of error
 */
int	open_outfiles(t_branch **tree)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = UNDEFINED_FD;
	while (tree[i] != NULL)
	{
		if (tree[i]->type == T_OUTFILE)
			fd = redirect_outfile(fd, tree[i]->elmnt);
		free(tree[i]);
		if (fd == E_FD)
			return (fd);
		i++;
	}
	return (fd);
}
