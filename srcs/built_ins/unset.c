/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:59:57 by acroue            #+#    #+#             */
/*   Updated: 2024/04/09 12:56:57 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the Env Var to remove is matches one in the Env.
 */
int	match_env_key(char *key, char *remove_var)
{
	size_t	var_len;

	var_len = length_until_char(remove_var, '=');
	if (var_len != length_until_char(key, '='))
		return (0);
	if (ft_strncmp(key, remove_var, var_len) != 0)
		return (0);
	if (key[var_len] != '\0' && key[var_len] != '=')
		return (0);
	return (1);
}

/**
 * @brief Removes var from the env and reallocates the env
 */
char	**remove_from_env(char **env, char *var)
{
	char	**new_env;
	size_t	i;
	size_t	offset;

	offset = 0;
	i = tab_len(env);
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i - 1] = NULL;
	i = 0;
	while (env[i])
	{
		if (match_env_key(env[i], var))
		{
			offset = 1;
			free(env[i]);
		}
		else
			new_env[i - offset] = env[i];
		i++;
	}
	return (free(env), new_env);
}

static int	is_valid_unset(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	unset_built_in(t_branch *branch)
{
	t_cmd	*cmd;
	t_env	*env;
	size_t	i;

	cmd = branch->elmnt;
	env = cmd->env;
	i = 1;
	while (cmd && cmd->args && cmd->args[i])
	{
		if (is_valid_unset(cmd->args[i]))
			env->env_tab = remove_from_env(env->env_tab, cmd->args[i]);
		i++;
	}
	return (0);
}

void	freetab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	t_branch	*br;
	t_cmd		*cmd;
	t_env		*env;
	int			err;

	env = make_env(envp);
	cmd = ft_calloc(1, sizeof(t_cmd));
	br = ft_calloc(1, sizeof(t_branch));
	cmd->env = env;
	cmd->args = argv;
	br->elmnt = cmd;
	export_print_env(br->elmnt, 1);
	err = unset_built_in(br);
	printf("\n");
	export_print_env(br->elmnt, 1);
	(void)argc;
	freetab(env->env_tab);
	return (free(env->env_tab), free(cmd), free(br), free(env), err);
}
