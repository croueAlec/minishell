/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:30:58 by acroue            #+#    #+#             */
/*   Updated: 2024/04/04 14:29:19 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Will remove invisible quotes from the Limiter
 * 
 * @param cmd The Command String.
 * @param lim The Limiter.
 * @param i (norme) The Limiter's index.
 */
void	fill_complex_lim(char *cmd, char *lim, size_t i)
{
	size_t	j;
	int		is_quote;
	char	curr_quote;

	curr_quote = cmd[0];
	is_quote = 1;
	j = 0;
	if (!lim)
		return ;
	while (cmd[++j])
	{
		if (is_quote < 0 && (cmd[j] == '\'' || cmd[j] == '\"'))
		{
			curr_quote = cmd[j];
			is_quote *= -1;
		}
		else if (cmd[j] == curr_quote)
			is_quote *= -1;
		else if (is_quote < 0 && (cmd[j] == ' ' || !cmd[j]))
			break ;
		else
			lim[i++] = cmd[j];
	}
}

char	*alloc_limiter(char **lim, size_t len)
{
	char	*tmp;

	tmp = ft_calloc((len + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	*lim = tmp;
	return (tmp);
}

/**
 * @brief Finds the Limiter in case of simple or double quotes.
 * 
 * @param cmd The Command String.
 * @param lim A pointer to the Limiter String.
 * @param i A pointer the the index in the Command String.
 * @param len (norme) The length of the limiter without invisible quotes.
 * @return int 0 if an error occured, 1 otherwise.
 */
int	find_complex_lim(char *cmd, char **lim, size_t *i, size_t len)
{
	size_t	j;
	int		is_quote;
	char	curr_quote;

	curr_quote = cmd[0];
	is_quote = 1;
	j = 1;
	while (cmd[j])
	{
		if (is_quote < 0 && (cmd[j] == '\'' || cmd[j] == '\"'))
		{
			curr_quote = cmd[j];
			is_quote *= -1;
		}
		else if (cmd[j] == curr_quote)
			is_quote *= -1;
		else if (is_quote < 0 && (cmd[j] == ' ' || !cmd[j]))
			break ;
		else
			len++;
		j++;
	}
	*i += j + 1;
	return (fill_complex_lim(cmd, alloc_limiter(lim, len), 0), 1);
}

/**
 * @brief Finds the Limiter
 * 
 * @param cmd The Command String.
 * @param i A pointer to the index in the Command String.
 * @param lim A pointer to the Limiter String.
 * @return int 0 if an error occured, 1 otherwise.
 */
int	find_lim(char *cmd, size_t *i, char **lim, int *is_expand)
{
	size_t	spaces;
	size_t	j;

	j = 0;
	spaces = 0;
	*i += 2;
	while (cmd[spaces] && cmd[spaces] == ' ')
		spaces++;
	if (!cmd[spaces] || cmd[spaces] == '|')
		return (0);
	if (cmd[spaces] == '<' || cmd[spaces] == '>')
		return (0);
	if (cmd[j + spaces] != '\'' && cmd[j + spaces] != '\"')
	{
		while (cmd[j + spaces] && cmd[j + spaces] != ' ')
			j++;
		*lim = ft_substr(cmd, spaces, j);
		*i += j + spaces;
		(*is_expand)++;
	}
	else
		return (find_complex_lim(&cmd[j + spaces], lim, i, 0));
	return (1);
}
