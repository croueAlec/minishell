/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:45:38 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/26 15:14:23 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars_list	*pars_list_new(t_pars_type type, char *content)
{
	t_pars_list	*node;
	
	node = malloc(sizeof(t_pars_list));
	if (!node)
		return (NULL);
	node->s = content;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_pars_list	*pars_list_last(t_pars_list *lst)
{
	while (lst)
	{
		if (!lst->next)
		{
			return (lst);
		}
		else
			lst = lst->next;
	}
	return (lst);
}

void	pars_list_add_back(t_pars_list **lst, t_pars_list *new)
{
	t_pars_list	*last;
	
	if (lst)
	{
		if (*lst)
		{
			last = pars_list_last(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

size_t	len_exp_args_or_redirect(char *s, size_t *i)
{
	size_t	len;
	char	quote;

	len = 0;
	while (s && s[*i + len] != 0 && s[*i + len] != '>' && s[*i + len] != '<')
	{
		len++;
		if (s[*i + len - 1] == '\"' || s[*i + len - 1] == '\'')
		{
			quote = s[*i + len - 1];
			while (s[*i + len] != quote)
				len++;
			len++;
		}
	}
	return (len);
}

t_pars_type	get_parsing_type(char **input, size_t *j, size_t *i)
{
	*i += 1;
	if (input[*j][*i - 1] == '>' && input[*j][*i] == '>')
	{
		*i += 1;
		return (PARS_APP_OUT);
	}
	if (input[*j][*i - 1] == '<' && input[*j][*i] == '<')
	{
		*i += 1;
		return (PARS_HERE_DOC);
	}
	if (input[*j][*i - 1] == '>' && input[*j][*i] != '>')
		return (PARS_TRUNC_OUT);
	if (input[*j][*i - 1] == '<' && input[*j][*i] != '<')
		return (PARS_IN);
	*i -= 1;
	if (input[*j][*i - 1] == '-')
		return (PARS_ARG);
	return (PARS_CMD);
}
