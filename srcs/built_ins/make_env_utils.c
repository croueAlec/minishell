/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:18:00 by acroue            #+#    #+#             */
/*   Updated: 2024/04/22 19:10:04 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_shlvl(t_env *env)
{
	size_t	i;
	char	**env_tab;

	i = 0;
	env_tab = env->env_tab;
	while (env_tab && env_tab[i])
	{
		if (ft_strncmp(env_tab[i], "SHLVL=", 6) == 0 && env_tab[i][6])
		{
			return (ft_atoi(&env_tab[i][6]));
		}
		i++;
	}
	return (0);
}

int	set_shlvl(t_env *env)
{
	int	shlvl;
	char	*level;
	char	*new_level;

	level = NULL;
	new_level = NULL;
	shlvl = find_shlvl(env);
	if (shlvl <= 0)
	{
		env->env_tab = add_to_env(env->env_tab, "SHLVL=1", 0);
		return (1);
	}
	level = ft_itoa(shlvl + 1);
	if (!level)
		return (0);
	new_level = ft_strjoin("SHLVL=", level);
	if (!new_level)
		return (free(level), 0);
	env->env_tab = add_to_env(env->env_tab, new_level, 0);
	return (free(level), free(new_level), 1);
}

/**
 * @brief Set the the PWD in the env, exits the shell upon failure.
 */
void	set_pwd_env(t_env *env)
{
	char	*pwd;
	char	*env_var;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ((void)ft_dprintf(2, ERRENV), free_and_exit(1, NULL, env));
	env_var = ft_strjoin("PWD=", pwd);
	if (!env_var)
		return ((void)ft_dprintf(2, ERRENV), free(pwd), \
		free_and_exit(1, NULL, env));
	free(pwd);
	env->env_tab = add_to_env(env->env_tab, env_var, 0);
	free(env_var);
}
