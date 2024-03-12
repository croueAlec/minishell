/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/12 11:57:49 by jblaye           ###   ########.fr       */
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
int			variable_len(char *variable, char **env);
char		*variable_value(char *variable, char **env);
void		expanded_len_variable(char *str, size_t *len, size_t *exp_len, char **env);
void		expanded_len_double_quote(char *str, size_t *len, size_t *exp_len, char **env);
size_t		expanded_len(size_t i, char *str, char **env);
void		dup_exp_var(char *result, char *str, size_t *index, char **env);
void		dup_exp_single_quote(char **result, char *str, size_t *index);
void		dup_exp_doubl_quote(char *gresult, char *str, size_t *index, char **env);
char		*dup_expanded_char(size_t i, char *str, char **env);


/// INPUT TREE GENERATION
/// Utils
int			str_tab_len(char **tab);
t_cmd		*new_cmd(void);
t_branch	*new_cmd_branch(void);
/// Core
void		generate_cmd_branches(t_branch *first, int len);
t_branch	*input_tree(char **input);

#endif
