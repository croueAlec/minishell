/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:09:12 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/20 14:19:29 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_str(char *s, char *result, char quote, size_t *index)
{
	while (s[index[0]] != quote)
	{
		result[index[1]] = s[index[0]];
		index[0] += 1;
		index[1] += 1;
	}
	index[0] += 1;
}

char	*expanded_quotes_dup(char *s, char c, int len)
{
	char	*result;
	size_t	*index;

	index = (size_t [2]) {0, 0};
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (s[index[0]] != c && s[index[0]] != 0)
	{
		index[0] += 1;
		if (s[index[0] - 1] == '\'' || s[index[0] - 1] == '\"')
			copy_str(s, result, s[index[0] - 1], index);
		else
		{
			result[index[1]] = s[index[0] - 1];
			index[1] += 1;
		}
	}
	return (result);
}

char	**quote_expansion_split(char *s, char c)
{
	char	**result;
	int		i;
	int		word_len;

	if (all_quotes_are_closed(s) == 0)
		return (NULL);
	result = ft_calloc(count_words_quotes(s, c) + 1, sizeof(char *));
	i = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
		{
			word_len = len_word_quotes(s, c);
			result[i] = expanded_quotes_dup(s, c, word_len);
			if (!result[i])
				return (ft_fsplit(result), NULL);
			i++;
		}
		s = s + word_len;
	}
	result[i] = NULL;
	return (result);
}
