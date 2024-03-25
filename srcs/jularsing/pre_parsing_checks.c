/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:48:00 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/25 09:26:04 by jblaye           ###   ########.fr       */
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

int	no_syntax_error(char *str)
{
	(void) str;
	// A CODER : si < suivi d'un caractere pas file, unexpected error near token 'le caractere en question'
	/// si | precede de rien, erreur syntax |
	/// la premiere erreur detectee dans la str est celle renvoyee
	/// si dernier caractere |, ouvre un prompt
	/// si fini par | > ou | < token erreur newline
	// size_t	i;
	// int		ispipe;
	// i = 0;
	// ispipe = 0;
	// while (str[i] != 0)
	// {
	// 	while (str[i] == ' ' || str[i] == '>' || str[i] == '<')
	// 		i++;
	// 	if (str[i] == '|' || (str[i] == 0 && ispipe == 1))
	// 		return (0);
	// 	while (str[i] != '|' && str[i] != 0)
	// 		i++;
	// 	if (str[i] == '|')
	// 	{
	// 		ispipe = 1;
	// 		i++;
	// 	}
	// }
	// if (str[i] == 0 && str[i - 1] == '|')
	// 	return (0);
	return (1);
}