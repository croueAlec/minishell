/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:05 by julieblaye        #+#    #+#             */
/*   Updated: 2024/04/24 13:38:29 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	variable_len(char *variable, t_env *env, size_t *len_a, size_t *len_b)
{
	size_t	i;
	char	*content;

	i = 0;
	if (ft_strncmp(variable, "?", 1) == 0)
	{
		*len_b = 1;
		if (env->err_no >= 10)
			*len_b = 2;
		if (env->err_no >= 100)
			*len_b = 3;
		*len_a = 1;
	}
	else
	{
		content = variable_value(variable, env);
		*len_b = ft_safe_strlen(content);
		while (ft_isalnum(variable[i]) == 1 || variable[i] == '_')
		{
			*len_a += 1;
			i++;
		}
	}
}

char	*variable_value(char *variable, t_env *env)
{
	size_t	i;
	size_t	len_var;

	i = 0;
	len_var = 0;
	if (is_question_mark_var(variable) == 1)
		return (ft_itoa(env->err_no));
	if (variable)
	{
		while (ft_isalnum(variable[i]) == 1 || variable[i] == '_')
		{
			len_var++;
			i++;
		}
	}
	i = 0;
	while (env->env_tab[i] != 0)
	{
		if (ft_strncmp(env->env_tab[i], variable, len_var) == 0
			&& (env->env_tab[i][len_var] == '=' || !env->env_tab[i][len_var]))
			return (&(env->env_tab)[i][len_var + 1]);
		i++;
	}
	return (NULL);
}

static void	set_values_zero(size_t *val_one, size_t *val_two)
{
	*val_one = 0;
	*val_two = 0;
}

size_t	var_expanded_len(char *str, t_env *env)
{
	size_t	len[2];
	size_t	var_len[2];

	set_values_zero(&len[0], &len[1]);
	set_values_zero(&var_len[0], &var_len[1]);
	while (str[len[LEN]] != 0)
	{
		len[LEN] += 1;
		if (str[len[LEN] - 1] == '\'')
			move_forward_single_quotes(len, str);
		else if (str[len[LEN] - 1] == '\"')
			move_forward_double_quotes(len, str, env);
		else if (str[len[LEN] - 1] == 36 && str[len[LEN]] \
		&& str[len[LEN]] != 32)
		{
			variable_len(&(str)[len[LEN]], env, &var_len[0], &var_len[1]);
			len[LEN] += var_len[LEN] - 1;
			len[EXP_LEN] += var_len[EXP_LEN];
		}
		else
			len[EXP_LEN] += 1;
		if (len[LEN] > 1 && !str[len[LEN] - 2])
			break ;
	}
	return (len[EXP_LEN]);
}

char	*str_expand_var(char *str, t_env *env)
{
	char	*result;
	size_t	index[2];

	result = (char *) ft_calloc(var_expanded_len(str, env) + 1, sizeof(char));
	index[0] = 0;
	index[1] = 0;
	if (!result)
		return (NULL);
	while (str[index[0]] != 0)
	{
		if (str[index[0]] == '\'')
			copy_single_quote(result, str, index);
		else if (str[index[0]] == '\"')
			copy_double_quote_expand(result, str, index, env);
		else if (str[index[0]] == 36 && (ft_isalpha(str[index[0] + 1]) \
		|| str[index[0] + 1] == '?'))
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
