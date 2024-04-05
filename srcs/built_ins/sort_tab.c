/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:14:06 by acroue            #+#    #+#             */
/*   Updated: 2024/04/05 18:59:00 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns 1 if s1 is smaller than s2.
 */
static int compare_str(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (s1[i] == '\0')
		return (1);
	else if (s2[i] == '\0')
		return (0);
	return (s1[i] < s2[i]);
}

static int	is_sorted(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i + 1] && !compare_str(tab[i], tab[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

/**
 * @brief Sorts a string array.
 */
char **sort_char_tab(char **tab)
{
	size_t	i;

	while (!is_sorted(tab))
	{
		i = 0;
		while (tab[i])
		{
			if (tab[i + 1] && !compare_str(tab[i], tab[i + 1]))
				ft_swap(&tab[i], &tab[i + 1]);
			i++;
		}
	}
	return (tab);
}

/* int	main(int argc, char *argv[])
{
	char	*tab[5] = {"b", "A", "aa", "a", 0};
	char	**res;

	res = sort_char_tab(tab);
	printf("%s\n", res[0]);
	printf("%s\n", res[1]);
	printf("%s\n", res[2]);
	printf("%s\n", res[3]);
	(void)argc;
	(void)argv;
	return (0);
}
 */
