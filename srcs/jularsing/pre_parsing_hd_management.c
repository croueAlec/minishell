/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_hd_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:39:32 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/03 17:37:01 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_fd_list_clear(t_hd_fd_list *lst)
{
	t_hd_fd_list	*tmp;

	if (lst)
	{
		tmp = lst;
		while (lst != NULL)
		{
			tmp = lst->next;
			free(lst);
			lst = tmp;
		}
	}
}

int	hd_fd_list_add_back(t_hd_fd_list **lst, int new_fd)
{
	t_hd_fd_list	*node;
	t_hd_fd_list	*last;

	if (lst)
	{
		node = ft_calloc(1, sizeof(t_hd_fd_list));
		if (!node)
			return (hd_fd_list_clear(lst), 0);
		node->fd = new_fd;
		node->next = NULL;
		if (!*lst)
			*lst = node;
		else
		{
			last = lst;
			while (last && last->next != 0)
				last = last->next;
			last->next = node;
		}
		return (1);
	}
	return (0);
}

void	get_heredoc_fd(t_hd_fd_list	*first)
{
	
}