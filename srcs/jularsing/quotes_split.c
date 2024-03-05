/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julieblaye <julieblaye@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:28:48 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/05 10:38:40 by julieblaye       ###   ########.fr       */
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

static char	*ft_strndup(char *src, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_calloc((n + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

void	ft_fsplit(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i] != 0)
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

char	**quotes_split(char *s, char c)
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
			result[i] = ft_strndup(s, word_len);
			if (!result[i])
				return (ft_fsplit(result), NULL);
		}
		s = s + word_len;
	}
}
