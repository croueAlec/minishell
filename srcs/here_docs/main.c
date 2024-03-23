/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:43:58 by acroue            #+#    #+#             */
/*   Updated: 2024/03/23 13:48:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_here_doc(char *lim, int *here_doc_fd)
{
	printf("\n{%s}\n", lim);
	(free(lim), lim = NULL);
	(void)here_doc_fd;
}

void	fill_complex_lim(char *str, char **lim, size_t len, size_t i)
{
	size_t	j;
	int		is_quote;
	char	curr_quote;
	char	*tmp;

	curr_quote = str[0];
	is_quote = 1;
	j = 1;
	tmp = ft_calloc((len + 1), sizeof(char));
	if(!tmp)
		return ;
	while (str[j])
	{
		if (is_quote < 0 && (str[j] == '\'' || str[j] == '\"'))
		{
			curr_quote = str[j];
			is_quote *= -1;
		}
		else if (str[j] == curr_quote)
			is_quote *= -1;
		else if (is_quote < 0 && (str[j] == ' ' || !str[j]))
			break ;
		else
			tmp[i++] = str[j];
		j++;
	}
	*lim = tmp;
	printf("%s\n", tmp);
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
	printf("%c[", curr_quote);
	while (str[j])
	{
		if (is_quote < 0 && (str[j] == '\'' || str[j] == '\"'))
		{
			curr_quote = str[j];
			is_quote *= -1;
			printf("%c[", curr_quote);
		}
		else if (str[j] == curr_quote && printf("]"))
			is_quote *= -1;
		else if (is_quote < 0 && (str[j] == ' ' || !str[j]))
			break ;
		else
		{
			printf("%c", str[j]);
			len++;
		}
		j++;
	}
	printf("]\t%zu", len);
	*i += j;
	return (fill_complex_lim(str, lim, len, 0), 1);
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
	if (!str[spaces] || str[spaces] == '|')
		return (0);
	if (str[spaces] == '<' || str[spaces] == '>')
		return (0);
	if (str[j + spaces] != '\'' && str[j + spaces] != '\"')
	{
		while (str[j + spaces] && str[j + spaces] != ' ')
			j++;
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
	(void)argv;
	return (0);
}
