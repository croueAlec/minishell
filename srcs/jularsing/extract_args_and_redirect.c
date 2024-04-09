/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args_and_redirect.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:40:59 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/04 13:52:25 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_quotes(size_t *i, size_t *len, char *result, char *s)
{
	char	quote;

	quote = s[*i - 1];
	while (s[*i] != quote)
	{	
		result[*len] = s[*i];
		*len += 1;
		*i += 1;
	}
	*i += 1;
}

char	*dup_args_or_redirect(char *s, size_t *i)
{
	size_t	len;
	char	*result;

	result = ft_calloc(len_exp_args_or_redirect(s, i) + 1, sizeof(char));
	if (!result)
		return (NULL);
	len = 0;
	while (s && s[*i] != 0 && s[*i] != '>' && s[*i] != '<')
	{
		*i += 1;
		if (s[*i - 1] == '\"' || s[*i - 1] == '\'')
			expand_quotes(i, &len, result, s);
		else
		{
			result[len] = s[*i - 1];
			len++;
		}
	}
	return (result);
}

void	extract_arg(t_pars_list	**args, char **input, size_t *j, size_t *i)
{
	char		*name;
	t_pars_type	type;
	t_pars_list	*arg;

	type = get_parsing_type(input, j, i);
	name = dup_args_or_redirect(input[*j], i);
	arg = pars_list_new(type, name);
	pars_list_add_back(args, arg);
}

void	extract_redir(t_pars_list **files, char **input, size_t *j, size_t *i)
{
	char		*name;
	t_pars_type	type;
	t_pars_list	*redir;

	type = get_parsing_type(input, j, i);
	if (input[*j][*i] == 0)
	{
		*j += 1;
		*i = 0;
	}
	name = dup_args_or_redirect(input[*j], i);
	redir = pars_list_new(type, name);
	pars_list_add_back(files, redir);
}

void	extract_input_data(char **input, t_pars_list **a, t_pars_list **f)
{
	t_pars_list	*args;
	t_pars_list	*files;
	size_t		j;
	size_t		i;

	j = 0;
	i = 0;
	args = NULL;
	files = NULL;
	while (input[j] != 0)
	{
		while (input[j][i] != 0)
		{
			if (input[j][i] == '>' || input[j][i] == '<')
				extract_redir(&files, input, &j, &i);
			else
				extract_arg(&args, input, &j, &i);
		}
		if (input[j])
			j++;
		i = 0;
	}
	*a = args;
	*f = files;
}
