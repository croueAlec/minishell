/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:16:50 by acroue            #+#    #+#             */
/*   Updated: 2024/03/15 11:26:20 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

# define ERR_REDIR "Redirection error free\n"

t_cmd		*open_close_redir(t_branch *branch);
void		open_redirections(int *infile, int *outfile, t_branch *branch);
int			open_infile(t_branch *branch, int infile);
void		free_infile_branch(t_branch *branch);
int			open_outfile(t_branch *branch, int outfile);
void		free_outfile_branch(t_branch *branch);

#endif
