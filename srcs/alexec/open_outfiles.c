/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:23:00 by acroue            #+#    #+#             */
/*   Updated: 2024/03/04 17:16:39 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_outfile_leaves(t_outfile *outfile)
{
	free(outfile->path);
	outfile->path = NULL;
	free(outfile);
}

int	redirect_outfile(int fd, t_outfile *outfile)
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
	return (fd);
}

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
