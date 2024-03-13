/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/13 14:50:56 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define LEN 0
# define EXP_LEN 1

/// QUOTES CHECK
int			all_quotes_are_closed(char *str);

/// QUOTES SPLIT
int			count_words_quotes(char *s, char c);
int			len_word_quotes(char *s, char c);
void		ft_fsplit(char **tab);
char		**quotes_split(char *s, char c);

/// INFILE MANAGEMENT
int			in_outfile_len(char *str);

/// VAR EXPAND MANAGEMENT
/// Utils
void		move_forward_single_quotes(size_t *len, char *str);
void		move_forward_double_quotes(size_t *len, char *str, char **env);
void		copy_single_quote(char *result, char *str, size_t *index);
void		copy_double_quote_expand(char *result, char *str, size_t *index, char **env);
void		single_var_expansion(size_t *index, char *str, char *result, char **env);
/// Expand variables
size_t		*variable_len(char *variable, char **env);
char		*variable_value(char *variable, char **env);
size_t		var_expanded_len(char *str, char **env);
char		*str_expand_var(char *str, char **env);
/// Expand quotes
char		**quote_expansion_split(char *s, char c);

/// CMD FETCHING
ssize_t		fetch_cmd_index(char **args);
char		**pathstab(char **ev);
char		*cmdpath(char *cmd, char **ev);
int			isbuiltin(char *cmd_name);
char		*fetch_cmd_path(char *cmd_name, char **env);

/// INPUT TREE GENERATION
/// Utils
int			str_tab_len(char **tab);
t_cmd		*new_cmd(void);
t_branch	*new_cmd_branch(void);
/// Core
void		generate_cmd_branches(t_branch *first, int len);
t_branch	*input_tree(char **input);

#endif
