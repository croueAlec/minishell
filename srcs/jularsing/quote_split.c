/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julieblaye <julieblaye@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:48:00 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/01 11:00:33 by julieblaye       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Checks whether all quotes are closed in the user input
/// @param str user input read with readline
/// @return 1 upon succes or 0 if at least one quote is not properly closed

int	all_quotes_are_closed(char *str)
{
	int	i;
	int	c;

	i = 0;
	if (str)
	{
		while (str[i] != 0)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				c = str[i];
				i++;
				while (str[i] != 0 && str[i] != c)
					i++;
				if (str[i] != c)
					return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

// char	**quote_split(char *str)
// {
	
// }