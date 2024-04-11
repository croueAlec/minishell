/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:42 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/11 15:18:00 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_env_param(char *name, char *new_value, t_env *env)
{
	int		i;
	int		len;
	char	*new_param;
	char	*malloc_name;

	i = 0;
	len = ft_safe_strlen(name);
	while (env->env_tab && env->env_tab[i] != 0)
	{
		if (ft_strncmp(name, env->env_tab[i], len) == 0
			&& env->env_tab[i][len] == 61)
		{
			malloc_name = ft_strdup(name);
			if (!malloc)
				return (ENOMEM);
			new_param = ft_sep_join(malloc_name, new_value, "=");
			if (!new_param)
				return (ENOMEM);
			free(env->env_tab[i]);
			env->env_tab[i] = new_param;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	cd_built_in(t_cmd *cd_cmd)
{
	char	*pwd;
	char	*env_pwd;

	if (cd_cmd->args[2] != NULL)
		return (ft_dprintf(2, "tacOS: cd: too many arguments\n"), 1);
	chdir(cd_cmd->args[1]);
	if (errno != 0)
		return (strerror(errno), errno);
	pwd = getcwd(0, 0);
	
	cd_cmd->env->err_no = 0;
	return (errno);
}
