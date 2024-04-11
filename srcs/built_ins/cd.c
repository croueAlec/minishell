/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:42 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/11 10:43:32 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_built_in(t_env *env, t_cmd *cd_cmd)
{
	if (cd_cmd->args[2] != NULL)
		return (ft_dprintf(2, "tacOS: cd: too many arguments\n"), 1);
	chdir(cd_cmd->args[1]);
	if (errno != 0)
	{
		env->err_no = errno;
		return (ft_dprintf(2, strerror(errno)), errno);
	}
	return (0);
}
