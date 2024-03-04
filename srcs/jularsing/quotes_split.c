/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:28:48 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/04 10:46:06 by jblaye           ###   ########.fr       */
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

// int	len_word_quotes(char *str, char c)
// {
	
// }

// char	**quotes_split(char *str)
// {
	
// }