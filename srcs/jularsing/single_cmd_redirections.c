/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:06:58 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/09 10:57:56 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	it_s_a_heredoc(t_infile	*infile, t_hd_fd_list *nxt_fd)
{
	t_hd_fd_list	*tmp;

	if (nxt_fd)
	{
		tmp = nxt_fd->next;
		infile->type = IT_HERE_DOC;
		infile->path = NULL;
		infile->fd = nxt_fd->fd;
		free(nxt_fd);
		nxt_fd = tmp;
	}
}

void	it_s_an_infile(t_branch *new_branch, t_pars_list *redir,
						t_hd_fd_list *nxt_fd)
{
	t_infile	*infile;

	new_branch->type = T_INFILE;
	infile = ft_calloc(1, sizeof(t_infile));
	if (!infile)
	{
		free(new_branch);
		new_branch = NULL;
		return ;
	}
	if (redir->type == PARS_IN)
	{
		infile->type = IT_RDONLY;
		infile->fd = -2;
		infile->path = ft_strdup(redir->s);
		if (!infile->path)
		{
			(free(infile), free(new_branch));
			new_branch = NULL;
			return ;
		}
	}
	if (redir->type == PARS_HERE_DOC)
		it_s_a_heredoc(infile, nxt_fd);
	new_branch->elmnt = infile;
}

void	it_s_an_outfile(t_branch *new_branch, t_pars_list *redir)
{
	t_outfile	*outfile;

	new_branch->type = T_OUTFILE;
	outfile = ft_calloc(1, sizeof(t_outfile));
	if (!outfile)
	{
		free(new_branch);
		new_branch = NULL;
		return ;
	}
	if (redir->type == PARS_APP_OUT)
		outfile->type = OT_APPEND;
	if (redir->type == PARS_TRUNC_OUT)
		outfile->type = OT_TRUNC;
	outfile->path = ft_strdup(redir->s);
	if (!outfile->path)
	{
		(free(outfile), free(new_branch));
		new_branch = NULL;
		return ;
	}
	new_branch->elmnt = outfile;
}

t_branch	*generate_redir_branch(t_pars_list	*redir,
									t_hd_fd_list *hd_fd_list)
{
	t_branch	*new_branch;

	new_branch = ft_calloc(1, sizeof(t_branch));
	if (!new_branch)
		return (NULL);
	if (redir->type == PARS_APP_OUT || redir->type == PARS_TRUNC_OUT)
		it_s_an_outfile(new_branch, redir);
	else if (redir->type == PARS_IN || redir->type == PARS_HERE_DOC)
		it_s_an_infile(new_branch, redir, hd_fd_list);
	else
	{
		free(new_branch);
		return (NULL);
	}
	return (new_branch);
}

void	free_branch_tab(t_branch **branch_tab)
{
	int			i;
	t_outfile	*tmp_out;
	t_infile	*tmp_in;

	i = 0;
	while (branch_tab[i] != 0)
	{
		if (branch_tab[i]->type == T_INFILE)
		{
			tmp_in = branch_tab[i]->elmnt;
			free(tmp_in->path);
		}
		else if (branch_tab[i]->type == T_OUTFILE)
		{
			tmp_out = branch_tab[i]->elmnt;
			free(tmp_out->path);
		}
		free(branch_tab[i]->elmnt);
		free(branch_tab[i]);
		i++;
	}
	free(branch_tab);
}
