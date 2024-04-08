/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:59:57 by acroue            #+#    #+#             */
/*   Updated: 2024/04/08 14:55:35 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes var from the env and reallocates the env
 */
char	**remove_from_env(char **env, char *var)
{
	char	**new_env;
	size_t	i;
	size_t	offset;
	size_t	var_len;

	offset = 0;
	var_len = (size_t)ft_safe_strlen(var);
	i = tab_len(env);
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i - 1] = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
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
