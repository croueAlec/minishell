/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:28:48 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/04 12:44:45 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words_quotes(char *s, char c)
{
	int		i;
	int		count;
	char	quote;
	
	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (s[i] != 0)
			count++;
		while (s[i] != c && s[i] != 0)
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quote = s[i];
				i++;
				while (s[i] != quote && s[i] != 0)
					i++;
			}
			i++;
		}
	}
	return (count);
}

int	len_word_quotes(char *s, char c)
{
	int		i;
	char	quote;
	
	i = 0;
	while (s[i] != 0 && s[i] != c)
	{
		if (s[i] == '\"' || s[i] == '\'')
			{
				quote = s[i];
				i++;
				while (s[i] != quote && s[i] != 0)
					i++;
			}
		i++;
	}
	return (i);
}

char	**quotes_split(char *str)
{
	char	**result;
	int		nb;

	if (all_quotes_are_closed(str) == 0)
		return (NULL);
	nb = count_words_quotes(str, ' ');
	result = ft_calloc()
}