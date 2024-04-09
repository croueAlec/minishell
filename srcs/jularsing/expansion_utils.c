/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:41:54 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/04 13:44:02 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_forward_single_quotes(size_t *len, char *str)
{
	len[EXP_LEN] += 2;
	while (str[len[LEN]] != '\'')
	{
		len[EXP_LEN] += 1;
		len[LEN] += 1;
	}
	len[LEN] += 1;
}

void	move_forward_double_quotes(size_t *len, char *str, char **env)
{
	size_t	*var_len;

	var_len = (size_t [2]){0, 0};
	len[EXP_LEN] += 2;
	while (str[len[LEN]] != '\"')
	{
		len[LEN] += 1;
		if (str[len[LEN] - 1] == 36)
		{
			var_len = variable_len(&(str)[len[LEN]], env);
			len[LEN] += var_len[LEN];
			len[EXP_LEN] += var_len[EXP_LEN];
		}
		else
			len[EXP_LEN] += 1;
	}
	len[LEN] += 1;
}

void	copy_single_quote(char *result, char *str, size_t *index)
{
	result[index[1]] = str[index[0]];
	index[1] += 1;
	index[0] += 1;
	while (str[index[0]] != '\'')
	{
		result[index[1]] = str[index[0]];
		index[1] += 1;
		index[0] += 1;
	}
	result[index[1]] = str[index[0]];
	index[0] += 1;
	index[1] += 1;
}

void	copy_double_quote_expand(char *result, char *str,
									size_t *index, char **env)
{
	result[index[1]] = str[index[0]];
	index[1] += 1;
	index[0] += 1;
	while (str[index[0]] != '\"')
	{
		if (str[index[0]] == 36)
			single_var_expansion(index, str, result, env);
		else
		{
			result[index[1]] = str[index[0]];
			index[1] += 1;
			index[0] += 1;
		}
	}
	result[index[1]] = str[index[0]];
	index[0] += 1;
	index[1] += 1;
}

void	single_var_expansion(size_t *index, char *str, char *result, char **env)
{
	char	*var_val;
	size_t	i;

	index[0] += 1;
	var_val = variable_value(&str[index[0]], env);
	i = 0;
	while (var_val && var_val[i] != 0)
	{
		result[index[1]] = var_val[i];
		index[1] += 1;
		i++;
	}
	i = 0;
	while (ft_isalnum(str[index[0] + i]) == 1 || str[index[0] + i] == '_')
		i++;
	index[0] += i;
}
