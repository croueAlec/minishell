/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:41:54 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/16 23:34:19 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_forward_double_quotes(size_t *len, char *str, t_env *env)
{
	size_t	var_len[2];

	var_len[0] = 0;
	var_len[1] = 0;
	len[EXP_LEN] += 2;
	while (str[len[LEN]] != '\"')
	{
		len[LEN] += 1;
		if (str[len[LEN] - 1] == 36)
		{
			variable_len(&(str)[len[LEN]], env, &var_len[0], &var_len[1]);
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
									size_t *index, t_env *env)
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

static void	expand_err_no(size_t *index, char *result, t_env *env)
{
	int	err_no;

	err_no = env->err_no;
	if (err_no >= 100)
	{
		result[index[1]] = '1';
		index[1] += 1;
		err_no = err_no % 100;
	}
	if (err_no >= 10)
	{
		result[index[1]] = err_no / 10 + '0';
		index[1] += 1;
		err_no = err_no % 10;
	}
	result[index[1]] = err_no + '0';
	index[1] += 1;
	index[0] += 1;
}

void	single_var_expansion(size_t *index, char *str, char *result, t_env *env)
{
	char	*var_val;
	size_t	i;

	index[0] += 1;
	if (is_question_mark_var(&str[index[0]]) == 1)
	{
		expand_err_no(index, result, env);
		return ;
	}
	else
	{
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
}
