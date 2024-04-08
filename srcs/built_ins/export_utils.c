/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:33:02 by acroue            #+#    #+#             */
/*   Updated: 2024/04/08 18:06:02 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_var(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (((i == 0 && !ft_isalpha(s[i])) || !ft_isalnum(s[i])) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

size_t	length_until_char(const char *str, char ch)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != ch)
	{
		i++;
	}
	return (i);
}

int	export_print_env(t_cmd *cmd, int fd_out)
{
	size_t	i;
	t_env	*env;

	i = 0;
	env = cmd->env;
	if (write(fd_out, " ", 0) < 0)
		return ((void)ft_dprintf(2, WRITE_FILE_FULL, "export"), 1);
	while (env && env->env_tab[i])
	{
		if (write(fd_out, "declare -x", 10) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "export"), 1);
		if (write(fd_out, env->env_tab[i], ft_safe_strlen(env->env_tab[i])) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "export"), 1);
		i++;
	}
	return (0);
}
