/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julieblaye <julieblaye@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/11 11:04:49 by julieblaye       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

/// INPUT TREE GENERATION
/// Utils
int			str_tab_len(char **tab);
t_cmd		*new_cmd(void);
t_branch	*new_cmd_branch(void);
/// Core
void		generate_cmd_branches(t_branch *first, int len);
t_branch	*input_tree(char **input);

#endif
