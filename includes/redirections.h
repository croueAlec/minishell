/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:16:50 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 10:24:58 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

int		open_infiles(t_branch **branch);
void	free_infile_leaves(t_infile *infile);
int		open_outfiles(t_branch **tree);
void	free_outfile_leaves(t_outfile *outfile);

#endif
