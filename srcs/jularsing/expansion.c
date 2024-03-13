/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:35:02 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/13 11:07:12 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief fetches the value of the variable at index[0] of str and copies it to result at index[1]
/// @param result str with all expansions performed up to index[1]
/// @param str str with no expansions performed
/// @param index [0] is the cursor in str, [1] is the cursor in result
/// @param env env parameters in a mallocked char array
void	dup_exp_var(char *result, char *str, size_t *index, char **env)
{
	char	*var_val;
	size_t	i;

	i = 0;
	var_val = variable_value(&str[index[0]], env);
	while (var_val[i] != 0)
	{
		result[index[1]] = var_val[i];
		index[1] += 1;
		i++;
	}
	while (ft_isalnum(str[index[0]]) == 1 || str[index[0]] == '_')
		index[0] += 1;
	index[1] -= 1;
}

/// @brief copies the quoted caracters from str to result without the quotes
/// @param result str with all expansions performed up to index[1]
/// @param str str with no expansions performed
/// @param index [0] is the cursor in str, [1] is the cursor in result
void	dup_exp_single_quote(char *result, char *str, size_t *index)
{
	result[index[1]] = str[index[0] - 1];
	index[1] += 1;
	while (str[index[0]] != '\'')
			{
				result[index[1]] = str[index[0]];
				index[1] += 1;
				index[0] += 1;
			}
	result[index[1]] = str[index[0]];
	index[0] += 1;
}

/// @brief copies the quoted caracters from str to result while performming var expansions
/// @param result str with all expansions performed up to index[1]
/// @param str str with no expansions performed
/// @param index [0] is the cursor in str, [1] is the cursor in result
/// @param env env parameters in a mallocked array
void	dup_exp_doubl_quote(char *result, char *str, size_t *index, char **env)
{
	result[index[1]] = str[index[0] - 1];
	index[1] += 1;
	while (str[index[0]] != '\"' && str[index[0]] != 0)
	{
		index[0] += 1;
		if (str[index[0] - 1] == 36)
			dup_exp_var(result, str, index, env);
		else
		{
			result[index[1]] = str[index[0] - 1];
			index[1] += 1;
		}
	}
	result[index[1]] = str[index[0]];
	index[0] += 1;
}

/// @brief copies str staring at index i to result while performming all expansions, end add \0 or the next white space
/// @param i start index
/// @param str str with no expansions performed 
/// @param env env parameters in mallocked array
/// @return str with all expansions performed
char	*dup_expanded_char(size_t i, char *str, char **env)
{
	size_t	len;
	char	*result;
	size_t	*index;

	len = expanded_len(i, str, env);
	result = (char *) ft_calloc(len + 1, sizeof(char));
	index = (size_t [2]) {i, 0};
	if (!result)
		return (NULL);
	while (str[index[0]] != ' ' && str[index[0]] != 0
			&& str[index[0]] != '>' && str[index[0]] != '<')
	{
		index[0] += 1;
		if (str[index[0] - 1] == '\'')
			dup_exp_single_quote(&result, str, index);
		else if (str[index[0] - 1] == '$')
			dup_exp_var(result, str, index, env);
		else if (str[index[0] - 1] == '\"')
			dup_exp_doubl_quote(result, str, index, env);
		else
			result[index[1]] = str[index[0] - 1];
		index[1] += 1;
	}
	return (result);
}
