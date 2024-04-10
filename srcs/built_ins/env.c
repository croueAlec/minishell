/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:34:21 by acroue            #+#    #+#             */
/*   Updated: 2024/04/10 16:29:19 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Condition to only print vars that have a value.
 */
static int find_char(char *str, char ch)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

int	env_built_in(t_cmd *cmd, int fd_out)
{
	size_t	i;
	t_env	*env;

	i = 0;
	env = cmd->env;
	if (write(fd_out, " ", 0) < 0)
		return ((void)ft_dprintf(2, ENV_WRITE_FULL, "env"), 125);
	while (env && env->env_tab[i])
	{
		if (!find_char(env->env_tab[i], '='))
		{
			i++;
			continue ;
		}
		if (write(fd_out, env->env_tab[i], ft_safe_strlen(env->env_tab[i])) < 0)
			return ((void)ft_dprintf(2, ENV_WRITE_FULL, "env"), 125);
		if (write(fd_out, "\n", 1) < 0)
			return ((void)ft_dprintf(2, ENV_WRITE_FULL, "env"), 125);
		i++;
	}
	return (0);
}
