/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julieblaye <julieblaye@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:05 by julieblaye        #+#    #+#             */
/*   Updated: 2024/03/11 11:18:37 by julieblaye       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	variable_len(char *variable, char **env)
{
	int		len;
	char	*content;

	len = 0;
	content = variable_value(variable, env);
	if (content)
		len = ft_strlen(content);
	return (len);
}

char	*variable_value(char *variable, char **env)
{
	size_t	i;
	size_t	len_var;

	i = 0;
	len_var = 0;
	if (variable)
		len_var = ft_strlen(variable);
	while (env[i] != 0)
	{
		if (ft_strncmp(env[i], variable, len_var) == 0 && env[i][len_var] == '=')
			return (&env[i][len_var + 1]);
		i++;
	}
	return (NULL);
}
