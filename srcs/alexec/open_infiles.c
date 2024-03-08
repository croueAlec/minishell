/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:15:40 by acroue            #+#    #+#             */
/*   Updated: 2024/03/08 18:10:51 by acroue           ###   ########.fr       */
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
	free(infile->path);
	infile->path = NULL;
	free(infile);
	free(branch);
}

int	open_here_doc(int fd)
{
	fd = open(HEREDOC_TEST_PATH, O_RDONLY);
	printf("Je suis un redirect de here_doc,");
	printf(" alec ne doit pas oublier de free ma struct !\n");
	return (fd);
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
		return (open_here_doc(infile_fd));
	printf("Je suis un redirect de infile\n");
	if (infile->type == IT_RDONLY)
	{
		infile_fd = open(infile->path, O_RDONLY);
		if (infile_fd < 0)
			return (perror(infile->path), free_infile_branch(branch), E_FD);
	}
	return (free_infile_branch(branch), infile_fd);
}
