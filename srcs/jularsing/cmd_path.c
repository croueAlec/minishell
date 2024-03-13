#include "minishell.h"

/// @brief Fetches the index of the start of the cmd in the cmd string
/// @param cmd_str string containing the cmd  if there is one as well as redirections and arguments
/// @return the index where the commands starts. IF there are in/outfiles but no cmd, returns -1. IF there aren't outfiles nor commands, returns -2.
ssize_t	fetch_cmd_index(char *cmd_str)
{	
	ssize_t	i;
	int		valid;

	i = 0;
	valid = 0;
	while (cmd_str && cmd_str[i] != 0)
	{
		while (cmd_str[i] == ' ')
			i++;
		if (cmd_str[i] == '<' || cmd_str[i] == '>')
		{
			if (cmd_str[i + 1] == cmd_str[i])
				i++;
			i = i + 1 + in_outfile_len(&cmd_str[i]);
			valid = 1;
		}
		if (cmd_str[i] != '>' && cmd_str[i] != '<'
			&& cmd_str[i] != ' ' && cmd_str[i] != 0)
			return (i);
	}
	if (cmd_str && cmd_str[i] == 0 && valid == 1)
		return (-1);
	return (-2);
}

/// @brief fetches in the env parameters the one starting with path then split it into a str array with : separator
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

/// @brief cmdpath parcours le tableau de chemins potentiels pour la commande cmd et renvoie la str qui correspond au bon chemin, null sinon
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
	
	builtins = (char *[]) {"echo", "cd", "pwd", "export", "unset", "env", "exit", 0};
	i = 0;
	while (builtins[i] != 0)
	{
		if (ft_strncmp(cmd_name, builtins[i], ft_strlen(builtins[i] + 1)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*fetch_cmd_path(char *cmd_str, char **env)
{
	ssize_t	i;
	char	*path;
	char	*cmd_name;

	path = NULL;
	cmd_name = NULL;
	i = fetch_cmd_index(cmd_str);
	if (i >= 0)
		cmd_name = dup_expanded_char(i, cmd_str, env);
	if (cmd_name && isbuiltin(cmd_name) == 1)
		return (free(cmd_name), NULL);
	if (cmd_name && ft_strchr(cmd_name, '/') != 0)
		return (cmd_name);
	else
		path = cmdpath(cmd_name, env);
	if (!path)
		return (free(cmd_name), NULL);
	return (free(cmd_name), path);
}
