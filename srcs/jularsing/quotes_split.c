/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:28:48 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/04 13:11:43 by jblaye           ###   ########.fr       */
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

char	**quotes_split(char *s, char c)
{
	char	**result;
	int		nb;
	int		i;

	if (all_quotes_are_closed(s) == 0)
		return (NULL);
	nb = count_words_quotes(s, ' ');
	result = ft_calloc(nb + 1, sizeof(char *));
	i = 0;
	nb = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
			nb = len_word_quotes(s, c);
		
	}
}
