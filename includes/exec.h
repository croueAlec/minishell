/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:12:39 by acroue            #+#    #+#             */
/*   Updated: 2024/04/16 20:02:20 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# define CMD_NOT_FOUND "%s: command not found\n"
# define NO_SUCH_FILE_OR_DIR "tacOS: %s: No such file or directory\n"

t_branch	*free_curr_branch(t_branch *branch);
int			is_path_unset(t_env *env);
void		define_execution_fd(int *fd_one, int *fd_two, int *fd_three);
int			is_cmd_path(char *cmd, char ch);
int			open_pipe(t_branch *branch, int pipefd[2], int tmp_outfile);
t_cmd		*handle_cmd_not_found(t_branch *branch, int *tmp_outfile);
t_cmd		*return_next_cmd(t_branch *branch);
void		cmd_error(t_branch *branch, char *err_msg);
void		redirection_error(t_branch *branch, size_t tree_index);
int			did_file_open_correctly(int infile, int outfile);
void		free_tab(void **tab);
void		free_cmd(t_cmd *cmd);
void		free_file_tree(t_branch **tree);
void		free_tree(t_branch *branch);
pid_t		execute_tree(t_branch *branch, t_env *env, size_t cmd_number);
void		differentiate_branches(t_branch *branch);
void		on_cmd_error(pid_t pid, t_branch *branch);

#endif
