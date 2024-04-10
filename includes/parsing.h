/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/10 15:00:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parsing_struct.h"

# define LEN 0
# define EXP_LEN 1

/// PRELEMINARY CHECK & HEREDOC OPEN
int			all_quotes_are_closed(char *str);
int			no_syntax_error(char *str, t_hd_fd_list **first, char **env);
/// heredoc utils
void		hd_fd_list_clear(t_hd_fd_list *lst);
int			hd_fd_list_add_back(t_hd_fd_list **lst, int new_fd);
int			lst_hd_fds(char *input, size_t i, t_hd_fd_list **first, char **env);

/// QUOTES SPLIT
int			count_words_quotes(char *s, char c);
int			len_word_quotes(char *s, char c);
void		ft_fsplit(char **tab);
char		**quotes_split(char *s, char c);

/// INFILE MANAGEMENT
int			in_outfile_len(char *str);

/// VAR EXPANSION
/// Utils
void		move_forward_single_quotes(size_t *len, char *str);
void		move_forward_double_quotes(size_t *len, char *str, char **env);
void		copy_single_quote(char *result, char *str, size_t *index);
void		copy_double_quote_expand(char *result, char *str,
				size_t *index, char **env);
void		single_var_expansion(size_t *index, char *str,
				char *result, char **env);
/// Expand variables
size_t	*variable_len(char *variable, char **env, size_t *len_a, size_t *len_b);
char		*variable_value(char *variable, char **env);
size_t		var_expanded_len(char *str, char **env);
char		*str_expand_var(char *str, char **env);

/// QUOTES EXPANSION
char		**quote_expansion_split(char *s, char c);

/// REDIRECTIONS AND ARGS EXTRACTION
/// Utils
t_pars_list	*pars_list_new(t_pars_type type, char *content);
t_pars_list	*pars_list_last(t_pars_list *lst);
void		pars_list_add_back(t_pars_list **lst, t_pars_list *new);
size_t		len_exp_args_or_redirect(char *s, size_t *i);
t_pars_type	get_parsing_type(char **input, size_t *j, size_t *i);
/// Core functions
void		expand_quotes(size_t *i, size_t *len, char *result, char *s);
char		*dup_args_or_redirect(char *s, size_t *i);
void		extract_arg(t_pars_list	**args, char **input, size_t *j, size_t *i);
void		extract_redir(t_pars_list **files, char **input,
				size_t *j, size_t *i);
void		extract_input_data(char **input, t_pars_list **a, t_pars_list **f);

/// SINGLE CMD BRANCH CREATION
/// Utils
int			pars_list_size(t_pars_list *lst);
void		pars_lst_clear(t_pars_list *lst);
/// Redirection utils
void		it_s_a_heredoc(t_infile	*infile, t_hd_fd_list *nxt_fd);
void		it_s_an_infile(t_branch *new_branch,
				t_pars_list *redir, t_hd_fd_list *nxt_fd);
void		it_s_an_outfile(t_branch *new_branch, t_pars_list *redir);
t_branch	*generate_redir_branch(t_pars_list	*redir,
				t_hd_fd_list *hd_fd_list);
void		free_branch_tab(t_branch **branch_tab);
/// Path fetching
char		**pathstab(char **ev);
char		*cmdpath(char *cmd, char **ev);
int			isbuiltin(char *cmd_name);
char		*fetch_cmd_path(char *cmd_name, char **env);
/// Core functions
t_branch	**generate_redir_tab(t_pars_list *files, t_hd_fd_list *hd_fd_list);
char		**generate_args_tab(t_pars_list *args);
t_cmd		*new_cmd(char **cmd_split, t_hd_fd_list *hd_fd_list, t_env *env);

/// INPUT TREE GENERATION
/// Utils
int			str_tab_len(char **tab);
t_branch	*new_cmd_branch(char *cmd, t_hd_fd_list *hd_fd_list, t_env *env);
/// Core functions
t_branch	*input_tree(char **input, t_hd_fd_list *hd_fd_list, t_env *env);

t_branch	*parsing(t_env *env);

#endif
