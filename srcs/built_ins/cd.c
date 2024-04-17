/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:42 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/17 05:20:31 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*full_env_parameter(char *name, char *value)
{
	char	*result;

	result = ft_strjoin(name, value);
	if (!result)
		return (free(value), NULL);
	return (free(value), result);
}

static void	update_pwd_and_oldpwd(char *pwd, char *old_pwd, t_env *env)
{
	int	i;
	int	yes;

	i = 0;
	yes = 0;
	while (env->env_tab && env->env_tab[i])
	{
		if (ft_strncmp("PWD=", env->env_tab[i], 4) == 0)
		{
			free(env->env_tab[i]);
			env->env_tab[i] = pwd;
		}
		if (ft_strncmp("OLDPWD=", env->env_tab[i], 7) == 0)
		{
			free(env->env_tab[i]);
			env->env_tab[i] = old_pwd;
			yes = 1;
		}
		i++;
	}
	if (yes == 0)
		env->env_tab = add_to_env(env->env_tab, old_pwd, &(env->err_no));
}

int	cd_built_in(t_cmd *cd_cmd)
{
	char	*tmp_pwd;
	char	*new_pwd;

	cd_cmd->env->err_no = 0;
	if (cd_cmd->args[1] != NULL && cd_cmd->args[2] != NULL)
		return (ft_dprintf(2, "tacOS: cd: too many arguments\n"), 1);
	if (cd_cmd->args[1] == NULL || !variable_value("PWD", cd_cmd->env))
		return (ft_dprintf(2, "tacOS: cd: please specify the path\n"), 1);
	tmp_pwd = ft_strdup(variable_value("PWD", cd_cmd->env));
	if (!tmp_pwd)
		return (ft_dprintf(2, CD_MALLOC_FAIL), ENOMEM);
	if (chdir(cd_cmd->args[1]) != 0)
		return (free(tmp_pwd), ft_dprintf(2, CD_NO_FILE, cd_cmd->args[1]), 1);
	new_pwd = getcwd(0, 0);
	if (!new_pwd)
		return (free(tmp_pwd), errno);
	tmp_pwd = full_env_parameter("OLDPWD=", tmp_pwd);
	if (!tmp_pwd)
		return (free(new_pwd), ft_dprintf(2, EXPORT_MALLOC_FAIL), ENOMEM);
	new_pwd = full_env_parameter("PWD=", new_pwd);
	if (!new_pwd)
		return (free(tmp_pwd), ft_dprintf(2, EXPORT_MALLOC_FAIL), ENOMEM);
	update_pwd_and_oldpwd(new_pwd, tmp_pwd, cd_cmd->env);
	return (cd_cmd->env->err_no);
}
