/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_branch_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:13:35 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/03 13:03:30 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pars_list_size(t_pars_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	pars_lst_clear(t_pars_list *lst)
{
	t_pars_list	*nxt;
	t_pars_list	*l;

	l = lst;
	if (lst)
	{
		while (l != 0)
		{
			nxt = l->next;
			free(l->s);
			free(l);
			l = nxt;
		}
		lst = NULL;
	}
}
