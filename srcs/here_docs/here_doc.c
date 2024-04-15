/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:43:58 by acroue            #+#    #+#             */
/*   Updated: 2024/04/15 19:35:14 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief This function finds and closes any here_doc FD in branch.
 */
void	track_and_close_hd_fd(t_branch *branch)
{
	size_t		i;
	t_cmd		*cmd;
	t_infile	*infile;

	i = 0;
	cmd = branch->elmnt;
	while (cmd && cmd->tree && cmd->tree[i] && cmd->tree[i]->elmnt)
	{
		if (cmd->tree[i]->type == T_INFILE)
		{
			infile = cmd->tree[i]->elmnt;
			if (infile->type == IT_HERE_DOC)
				close(infile->fd);
		}
		i++;
	}
}

int	is_here_doc(char *str)
{
	if (str[0] != '<')
		return (0);
	if (str[1] != '<')
		return (0);
	if (!str[2])
		return (0);
	return (1);
}

int	get_heredoc_fd(char *str, t_env *env)
{
	size_t	i;
	char	*lim;
	int		here_doc_fd;
	int		is_expand;

	is_expand = 0;
	here_doc_fd = UNDEFINED_FD;
	i = 0;
	lim = NULL;
	if (find_lim(&str[i + 2], &i, &lim, &is_expand))
	{
		if (!lim)
			return ((void)ft_dprintf(2, "malloc fail\n"), -1);
		create_here_doc(lim, &here_doc_fd, is_expand, env);
	}
	return (here_doc_fd);
}

/* int	main(int argc, char *argv[])
{
	size_t	i;
	char	*str;
	char	*lim;
	int		here_doc_fd;
	int		is_expand;

	is_expand = 0;
	here_doc_fd = UNDEFINED_FD;
	i = 0;
	str = argv[1];
	lim = NULL;
	if (argc != 2)
		return ((void)ft_dprintf(2, "bad arg nbr, use ./a.out 'string'\n"), -1);
	while (str[i])
	{
		if (is_here_doc(&str[i]) && find_lim(&str[i + 2], &i, &lim, &is_expand))
		{
			create_here_doc(lim, &here_doc_fd, is_expand);
			if (!lim)
				return ((void)ft_dprintf(2, "malloc fail\n"), -1);
		}
		else
			printf("%c", str[i++]);
	}
	return (0);
} */
