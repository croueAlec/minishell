/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:15:40 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 09:53:25 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infile_leaves(t_infile *infile)
{
	free(infile->path);
	infile->path = NULL;
	free(infile);
}

int	open_here_doc(int fd)
{
	if (fd >= 0)
		close(fd);
	fd = open(HEREDOC_TEST_PATH, O_RDONLY);
	return (fd);
}

int	redirect_infile(int fd, t_infile *infile)
{
	if (infile->type == IT_HERE_DOC)
		return (open_here_doc(fd));
	if (fd >= 0)
		close(fd);
	printf("Je suis un redirect de infile\n");
	if (infile->type == IT_RDONLY)
	{
		fd = open(infile->path, O_RDONLY);
		if (fd < 0)
			return (perror(infile->path), free_infile_leaves(infile), E_FD);
	}
	return (free_infile_leaves(infile), fd);
}

int	open_infiles(t_branch **tree)
{
	size_t	i;
	int		fd;

	i = 0;
	fd = UNDEFINED_FD;
	while (tree[i] != NULL)
	{
		if (tree[i]->type == T_INFILE)
			fd = redirect_infile(fd, tree[i]->elmnt);
		if (fd == E_FD)
			return (fd);
		i++;
	}
	return (fd);
}
