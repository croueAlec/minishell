/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:05 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/13 15:38:29 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	*variable_len(char *variable, char **env)
{
	size_t	*len;
	size_t	i;
	char	*content;

	len = (size_t [2]) {0, 0};
	i = 0;
	content = variable_value(variable, env);
	if (content)
	{
		len[1] = ft_strlen(content);
		while (ft_isalnum(variable[i]) == 1 || variable[i] == '_')
		{
			len[0] += 1;
			i++;
		}
	}
	return (len);
}

char	*variable_value(char *variable, char **env)
{
	size_t	i;
	size_t	len_var;

	i = 0;
	len_var = 0;
	if (variable)
	{
		while (ft_isalnum(variable[i]) == 1 || variable[i] == '_')
		{
			len_var++;
			i++;
		}
	}
	i = 0;
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], variable, len_var) == 0 && env[i][len_var] == '=')
			return (&env[i][len_var + 1]);
		i++;
	}
	return (NULL);
}

size_t	var_expanded_len(char *str, char **env)
{
	size_t	*len;
	size_t	*var_len;

	len = (size_t [2]){0, 0};
	var_len = (size_t [2]) {0, 0};
	while (str[len[LEN]] != 0)
	{
		len[LEN] += 1;
		if (str[len[LEN] - 1] == '\'')
			move_forward_single_quotes(len, str);
		else if (str[len[LEN] - 1] == '\"')
			move_forward_double_quotes(len, str, env);
		else if (str[len[LEN] - 1] == 36)
		{
			var_len = variable_len(&(str)[len[LEN]], env);
			len[LEN] += var_len[LEN];
			len[EXP_LEN] += var_len[EXP_LEN];
		}
		else
			len[EXP_LEN] += 1;
	}
	return (len[EXP_LEN]);
}

char	*str_expand_var(char *str, char **env)
{
	char	*result;
	size_t	*index;

	result = (char *) ft_calloc(var_expanded_len(str, env) + 1, sizeof(char));
	index = (size_t [2]) {0, 0};
	if (!result)
		return (NULL);
	while (str[index[0]] != 0)
	{
		if (str[index[0]] == '\'')
			copy_single_quote(result, str, index);
		else if (str[index[0]] == '\"')
			copy_double_quote_expand(result, str, index, env);
		else if (str[index[0]] == 36)
			single_var_expansion(index, str, result, env);
		else
		{
			result[index[1]] = str[index[0]];
			index[1] += 1;
			index[0] += 1;
		}
	}
	return (result);
}
