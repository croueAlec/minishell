/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/03 17:02:35 by jblaye           ###   ########.fr       */
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

/// PRELEMINARY CHECK
int				all_quotes_are_closed(char *str);
t_hd_fd_list	*no_syntax_error(char *str);

/// QUOTES SPLIT
int				count_words_quotes(char *s, char c);
int				len_word_quotes(char *s, char c);
void			ft_fsplit(char **tab);
char			**quotes_split(char *s, char c);

/// INFILE MANAGEMENT
int				in_outfile_len(char *str);

/// VAR EXPANSION
/// Utils
void			move_forward_single_quotes(size_t *len, char *str);
void			move_forward_double_quotes(size_t *len, char *str, char **env);
void			copy_single_quote(char *result, char *str, size_t *index);
void			copy_double_quote_expand(char *result, char *str, size_t *index, char **env);
void			single_var_expansion(size_t *index, char *str, char *result, char **env);
/// Expand variables
size_t			*variable_len(char *variable, char **env);
char			*variable_value(char *variable, char **env);
size_t			var_expanded_len(char *str, char **env);
char			*str_expand_var(char *str, char **env);

/// QUOTES EXPANSION
char			**quote_expansion_split(char *s, char c);

/// REDIRECTIONS AND ARGS EXTRACTION
/// Utils
t_pars_list		*pars_list_new(t_pars_type type, char *content);
t_pars_list		*pars_list_last(t_pars_list *lst);
void			pars_list_add_back(t_pars_list **lst, t_pars_list *new);
size_t			len_exp_args_or_redirect(char *s, size_t *i);
t_pars_type		get_parsing_type(char **input, size_t *j, size_t *i);
/// Core functions
void			expand_quotes(size_t *i, size_t *len, char *result, char *s);
char			*dup_args_or_redirect(char *s, size_t *i);
void			extract_arg(t_pars_list	**args, char **input, size_t *j, size_t *i);
void			extract_redir(t_pars_list **files, char **input, size_t *j, size_t *i);
void			extract_input_data(char **input, t_pars_list **a, t_pars_list **f);

/// CMD PATH FETCHING
char			**pathstab(char **ev);
char			*cmdpath(char *cmd, char **ev);
int				isbuiltin(char *cmd_name);
char			*fetch_cmd_path(char *cmd_name, char **env);

/// SINGLE CMD BRANCH CREATION
/// Utils
int				pars_list_size(t_pars_list *lst);
void			pars_lst_clear(t_pars_list *lst);
t_branch		**generate_redir_tab(t_pars_list *files, int fd);
char			**generate_args_tab(t_pars_list *args);
/// Core functions
t_cmd			*new_cmd(char **cmd_split, int hd_fd, char **env);

/// INPUT TREE GENERATION
/// Utils
int				str_tab_len(char **tab);
t_branch		*new_cmd_branch(char *cmd, int hd_fd, char **env);
/// Core functions
t_branch		*input_tree(char **input, int hd_fd, char **env);

t_branch		*parsing(char **env);

#endif
