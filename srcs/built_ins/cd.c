/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:25:42 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/10 14:41:03 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_built_in(t_env env, t_cmd *cd_cmd)
{
	if (cd_cmd->args[2] != NULL)
		return (ft_dprint(2, "tacOS: cd: too many arguments\n"), 1);
	
}