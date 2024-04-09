/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:46 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/04 13:50:33 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief builds a char** table of potential paths
/// @param ev array with mallocked env variables
/// @return the cmd path
char	**pathstab(char **ev)
{
	size_t	i;
	char	**paths;

	i = 0;
	if (!ev || !ev[0])
		return (NULL);
	while (ev[i] && ft_strncmp("PATH=", ev[i], 5) != 0)
		i++;
	if (ft_strncmp("PATH=", ev[i], 5) != 0)
		return (NULL);
	paths = ft_split(ev[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

/// @brief finds the path of the cmd, returns null otherwise
/// @param cmd name of the cmd
/// @param ev array with mallocked env variables
/// @return the cmd path if found null otherwise
char	*cmdpath(char *cmd, char **ev)
{
	int		i;
	char	**paths;
	char	*cmd_name;
	char	*cmd_path;

	i = 0;
	paths = pathstab(ev);
	if (!paths)
		return (ft_dprintf(2, "Command '%s' not found\n", cmd), NULL);
	cmd_name = ft_strjoin("/", cmd);
	if (!cmd_name)
		return (ft_dprintf(2, "Command '' not found\n"), ft_fsplit(paths), NULL);
	while (paths[i] != 0)
	{	
		cmd_path = ft_strjoin(paths[i], cmd_name);
		if (!cmd_path)
			return (free(cmd_name), ft_fsplit(paths), NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_fsplit(paths), free(cmd_name), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_dprintf(2, "Command '%s' not found\n", cmd);
	return (free(cmd_name), ft_fsplit(paths), NULL);
}

/// @brief checks wether the cmd is a builtin cmd
/// @param cmd_name name of the cmd without arguments
/// @return 
int	isbuiltin(char *cmd_name)
{
	char	**builtins;
	int		i;

	builtins = (char *[]){"echo", "cd", "pwd", "export",
		"unset", "env", "exit", 0};
	i = 0;
	while (builtins[i] != 0)
	{
		if (ft_strncmp(cmd_name, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*fetch_cmd_path(char *cmd_name, char **env)
{
	char	*path;
	char	*result;

	path = NULL;
	if (cmd_name && isbuiltin(cmd_name) == 1)
		return (NULL);
	if (cmd_name && ft_strchr(cmd_name, '/') != 0)
	{
		result = ft_strdup(cmd_name);
		if (result)
			return (result);
		return (NULL);
	}
	else
		path = cmdpath(cmd_name, env);
	if (!path)
		return (NULL);
	return (path);
}
