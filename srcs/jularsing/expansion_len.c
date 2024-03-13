/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:05 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/13 11:05:18 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Gets the len of the env variable value (after the =)
/// @param variable the env variable we seak
/// @param env the env variables char **
/// @return the len of what is after the =, ie if the var is TRUC and we have TRUC=truc in env, returns 4
int	variable_len(char *variable, char **env)
{
	int		len;
	char	*content;

	len = 0;
	content = variable_value(variable, env);
	if (content)
		len = ft_strlen(content);
	return (len);
}

/// @brief Gets the value of the env variable which name is variable
/// @param variable name of the variable ie PATH
/// @param env char ** which countains all the env variables (mallocked copy of the one in main)
/// @return value of the variable ie for PATH would return /bin/:/var/truc:... etc
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

/// @brief add the len of the variable when expanded to exp len int while incrementing len when progressing on the string
/// @param str pointer to the beginning of the str which is not a space
/// @param len index at which the variable starts, right after the $
/// @param exp_len size of the string up to the index len -1 when all previous variables have been expanded and quotes deleted
/// @param env char array containing the environment variables
void	expanded_len_variable(char *str, size_t *len, size_t *exp_len, char **env)
{
	*exp_len += variable_len(&str[*len], env);
	while (ft_isalnum(str[*len]) == 1 || str[*len] == '_')
		*len = *len + 1;
}

/// @brief add the len of the char between quotes when all variables within have been expanded, withou counting the quotes
/// @param str pointer to the beginning of the str which is not a space
/// @param len index at which the quoted portion of the str starts, right after the "
/// @param exp_len size of the string up to the index len - 1 when all previous variables have been expanded and quotes deleted
/// @param env char array containing the environment variables
void	expanded_len_double_quote(char *str, size_t *len, size_t *exp_len, char **env)
{
	*exp_len += 1;
	while (str[*len] != '\"' && str[*len] != 0)
	{
		*len+= 1;
		if (str[*len - 1] == 36)
			expanded_len_variable(str, len, exp_len, env);
		else
			*exp_len += 1;
	}
	*len += 1;
	*exp_len += 1;
}

/// @brief calculates the len of str when quotes have been deleted and var expanded, up until the next ' ' or \0
/// @param i index at which we start, str[i] being a caracter different than ' '
/// @param str string we aim to expand
/// @param env char array containing the environment variables
/// @return the final size of the str when all expension have been performed
size_t	expanded_len(size_t i, char *str, char **env)
{
	size_t	*len;

	len = (size_t [2]){i, 0};
	while (str[len[LEN]] != 0 && str[len[LEN]] != ' '
			&& str[len[LEN]] != '>' && str[len[LEN]] != '<')
	{
		len[LEN]++;
		if (str[len[LEN] - 1] == '\'')
		{
			len[EXP_LEN] += 2;
			while (str[len[LEN]] != '\'')
			{
				len[LEN]++;
				len[EXP_LEN]++;
			}
			len[LEN]++;
		}
		else if (str[len[LEN] - 1] == '\"')
			expanded_len_double_quote(str, &len[LEN], &len[EXP_LEN], env);
		else if (str[len[LEN] - 1] == 36)
			expanded_len_variable(str, &len[LEN], &len[EXP_LEN], env);
		else if (str[len[LEN]] != 0 && str[len[LEN]] != ' ')
			len[EXP_LEN]++;
	}
	return (len[EXP_LEN]);
}
