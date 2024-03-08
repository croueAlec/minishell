/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:16:50 by acroue            #+#    #+#             */
/*   Updated: 2024/03/08 17:16:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "minishell.h"

int		open_infile(t_branch *branch, int infile);
void	free_infile_branch(t_infile *infile);
int		open_outfile(t_branch *branch, int outfile);
void	free_outfile_branch(t_branch *branch);

#endif
