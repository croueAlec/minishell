/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:34:21 by acroue            #+#    #+#             */
/*   Updated: 2024/04/08 17:46:22 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (write(fd_out, env->env_tab[i], ft_safe_strlen(env->env_tab[i])) < 0)
			return ((void)ft_dprintf(2, ENV_WRITE_FULL, "env"), 125);
		if (write(fd_out, "\n", 1))
			return ((void)ft_dprintf(2, ENV_WRITE_FULL, "env"), 125);
		i++;
	}
	return (0);
}
