/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:12:39 by acroue            #+#    #+#             */
/*   Updated: 2024/04/02 17:48:53 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

t_branch	*free_curr_branch(t_branch *branch);
void		define_execution_fd(int *fd_one, int *fd_two, int *fd_three);
int			is_cmd_path(char *cmd, char ch);
t_cmd		*return_next_cmd(t_branch *branch);
void		cmd_error(t_branch *branch, char *err_msg);
void		redirection_error(t_branch *branch, size_t tree_index);
int			did_file_open_correctly(int infile, int outfile);
void		free_tab(void **tab);
void		free_cmd(t_cmd *cmd);
void		free_file_tree(t_branch **tree);
void		free_tree(t_branch *branch);
void		execute_tree(t_branch *branch, char **env);
void		differentiate_branches(t_branch *branch);

#endif
