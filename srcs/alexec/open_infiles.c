/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:15:40 by acroue            #+#    #+#             */
/*   Updated: 2024/03/05 11:05:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the contents of the Infile Struct. The branches themselves get 
 * freed in open_outfiles();
 * 
 * @param infile The Infile Struct
 */
static void	free_infile_leaves(t_infile *infile)
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

/**
 * @brief Opens either the here_doc or infile depending on infile type.
 * Prints an error message in case of error
 * 
 * @param fd The file descriptor of the previously opened infile, or 
 * UNDEFINED_FD if this is the first file
 * @param infile The Infile Struct indicating what to open and how
 * @return int The file descriptor of the opened infile or E_FD in case of
 *  error
 */
static int	redirect_infile(int fd, t_infile *infile)
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

/**
 * @brief Opens infiles (or here_docs) and makes sure they all exist and have 
 * the right permissions
 * @param tree An array of branches from the AST, parameters of the CMD Struct
 * @return int The last opened infile in case of success or E_FD (-1) in case of
 * error
 */
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
