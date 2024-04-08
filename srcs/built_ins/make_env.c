/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:19:58 by acroue            #+#    #+#             */
/*   Updated: 2024/04/08 15:27:56 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **sort_char_tab(char **tab);

size_t	tab_len(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		i++;
	}
	return (i);
}

static char	**dup_tab(char **tab, size_t len)
{
	char	**new_tab;
	size_t	i;

	i = 0;
	new_tab = ft_calloc(len + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	while (tab && tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	return (new_tab);
}

t_env	*make_env(char **env_tab)
{
	size_t	len;
	t_env	*env;

	len = tab_len(env_tab);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->err_no = 0;
	env->env_tab = dup_tab(env_tab, len);
	if (!env->env_tab)
		return (free(env), NULL);
	return (env);
}

/* int	main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	size_t	i;

	i = 0;
	env = make_env(envp);
	while (env->env_tab && env->env_tab[i])
	{
		printf("[%s]\n", env->env_tab[i]);
		i++;
	}
	i = 0;
	env->env_tab =  sort_char_tab(env->env_tab);
	printf("\n\n\n\n");
	env->env_tab = remove_from_env(env->env_tab, "SHELL");
	while (env->env_tab && env->env_tab[i])
	{
		printf("[%s]\n", env->env_tab[i]);
		i++;
	}
	printf("\n\n\n\n");
	i = 0;
	env->env_tab = add_to_env(env->env_tab, ft_strdup("SHELL=\"b\""));
	env->env_tab =  sort_char_tab(env->env_tab);
	while (env->env_tab && env->env_tab[i])
	{
		printf("[%s]\n", env->env_tab[i]);
		free(env->env_tab[i]);
		i++;
	}
	free(env->env_tab);
	free(env);
	(void)argc;
	(void)argv;
	return (0);
} */
