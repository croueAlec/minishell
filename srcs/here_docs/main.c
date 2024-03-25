/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:43:58 by acroue            #+#    #+#             */
/*   Updated: 2024/03/25 15:03:55 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "here_doc.h"

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

int	main(int argc, char *argv[])
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
}
