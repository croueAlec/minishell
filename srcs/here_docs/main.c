/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:43:58 by acroue            #+#    #+#             */
/*   Updated: 2024/03/22 18:08:07 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_here_doc(char *lim, int *here_doc_fd)
{
	printf("{%s}\n", lim);
	(free(lim), lim = NULL);
	(void)here_doc_fd;
}

int	find_complex_lim(char *str, char **lim, size_t *i)
{
	size_t	j;
	int		is_quote;
	char	curr_quote;
	size_t	len;

	curr_quote = str[0];
	is_quote = 1;
	j = 1;
	len = 0;
	while (str[j])
	{
		if (str[j] == curr_quote)
			is_quote *= -1;
		if (is_quote < 0 && str[j] == ' ')
			break ;
		j++;
		len++;
	}
	printf("%zu", len);
	(void)lim;
	(void)i;
	return (1);
}

int	find_lim(char *str, size_t *i, char **lim)
{
	size_t	spaces;
	size_t	j;

	j = 0;
	spaces = 0;
	*i += 2;
	while (str[spaces] && str[spaces] == ' ')
		spaces++;
	if (str[j + spaces] != '\'' || str[j + spaces] != '\"')
	{
		while (str[j + spaces] && str[j + spaces] != ' ')
			j++;
		if (str[j + spaces] == '\0')
			return (0);
		*lim = ft_substr(str, spaces, j);
		*i += j + spaces;
	}
	else
		return (find_complex_lim(&str[j + spaces], lim, i));
	return (1);
}

int	parse_here_doc(char *str)
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

	here_doc_fd = UNDEFINED_FD;
	i = 0;
	str = argv[1];
	lim = NULL;
	if (argc != 2)
		return ((void)ft_dprintf(2, "bad arg nbr, use ./a.out 'string'\n"), -1);
	while (str[i])
	{
		if (parse_here_doc(&str[i]) && find_lim(&str[i + 2], &i, &lim))
		{
			fill_here_doc(lim, &here_doc_fd);
			if (!lim)
				return ((void)ft_dprintf(2, "malloc fail\n"), -1);
		}
		else
		{
			printf("%c", str[i]);
		// 	return ((void)ft_dprintf(2, "parsing error\n"), -1);
			i++;
		}
	}
	return (0);
}
