#include "minishell.h"

/// @brief Fetches the index of the start of the cmd in the cmd string
/// @param cmd_str string containing the cmd  if there is one as well as redirections and arguments
/// @return the index where the commands starts. IF there are in/outfiles but no cmd, returns -1. IF there aren't outfiles nor commands, returns -2.
int	fetch_cmd_index(char *cmd_str)
{	
	size_t	i;
	int		valid;

	i = 0;
	valid = 0;
	while (cmd_str && cmd_str[i] != 0)
	{
		while (cmd_str[i] == ' ')
			i++;
		if (cmd_str[i] == '<' || cmd_str[i] == '>')
		{
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
/*
/// @brief returns the number of char in the command ex for ls returns 2, for "ls" returns 2
/// @param cmd_str the string containing the cmd as well as redirection files and arguments
/// @param cmd_index the index at which the command starts in the cmd str
/// @return the len of the command string
int	fetch_cmd_len(char *cmd_str, int cmd_index)
{
	int	i;

	i = 0;
	while (cmd_str[i + cmd_index])
}

char	*fetch_cmd_name(char *cmd_str, int cmd_len)
{

}

char	*fetch_cmd_path(char *cmd_str)
{
	int	len;

}


void	fill_cmd_token(char *input, t_branch *branch)
{
	t_cmd	*cmd;

	cmd = branch->elmnt;
	cmd->cmd_path = fetch_cmd_path(input);
}*/