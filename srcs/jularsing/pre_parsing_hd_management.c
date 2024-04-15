/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_hd_management.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:39:32 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/15 12:13:11 by jblaye           ###   ########.fr       */
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
			close(lst->fd);
			free(lst);
			lst = tmp;
		}
		lst = NULL;
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
			return (hd_fd_list_clear(*lst), 0);
		node->fd = new_fd;
		node->next = NULL;
		if (!*lst)
			*lst = node;
		else
		{
			last = *lst;
			while (last->next != 0)
				last = last->next;
			last->next = node;
		}
		return (1);
	}
	return (0);
}

int	lst_hd_fds(char *input, size_t i, t_hd_fd_list **first, t_env *env)
{
	int	hd_fd;

	hd_fd = get_heredoc_fd(&input[i], env);
	return (hd_fd_list_add_back(first, hd_fd));
}
