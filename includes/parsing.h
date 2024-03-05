/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:43:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/05 18:58:38 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/// QUOTES CHECK
int		all_quotes_are_closed(char *str);

/// QUOTES SPLIT
int		count_words_quotes(char *s, char c);
int		len_word_quotes(char *s, char c);
void	ft_fsplit(char **tab);
char	**quotes_split(char *s, char c);

#endif
