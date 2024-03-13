/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   built_ins_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:04:43 by acroue            #+#    #+#             */
/*   Updated: 2024/03/13 17:31:32 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds which built-in is supposed to be executed.
 * 
 * @param branch The current CMD Branch.
 * @return int A positive number if a built-in is recognized, 0 on error.
 */
static int	is_built_in(t_branch *branch)
{
	t_cmd	*cmd;
	char	*cmd_name;
	char	**builtins;
	int		i;

	cmd = branch->elmnt;
	cmd_name = cmd->args[0];
	builtins = (char *[]){BI_ECHO, BI_PWD, BI_EXPORT, BI_ENV, BI_CD, BI_UNSET, \
BI_EXIT, 0};
	i = 0;
	if (!cmd_name)
		return ((void)ft_dprintf(2, E_NULL_BUILTIN), 0);
	while (builtins[i] != 0)
	{
		if (ft_strncmp(cmd_name, builtins[i], ft_strlen(builtins[i] + 1)) == 0)
			return (i + 1);
		i++;
	}
	return ((void)ft_dprintf(2, "%s : %s", cmd_name, E_NO_BUILTIN), B_ERR);
}

/**
 * @brief Calls upon the built-ins that print a message on an output, such as 
 * echo, pwd, export and env.
 * 
 * @param branch The current CMD Branch.
 * @param type The built-in's index in the e_builtin enum.
 * @param fd_out The file descriptor on which to execute the built-in.
 * @param cmd_nbr The current command number inside the pipeline.
 */
void	printing_bltin(t_branch *branch, t_bltin type, int fd_out, int *cmd_nbr)
{
	if (fd_out == UNDEFINED_FD)
		fd_out = STDOUT_FILENO;
	if (type == B_ECHO)
		ft_dprintf(fd_out, "je suis un echo, echo, echo, echo...\n");
	else if (type == B_PWD)
		ft_dprintf(fd_out, "je suis un pwd, /home/acroue/Documents\n");
	else if (type == B_EXPORT)
		ft_dprintf(fd_out, "je suis un export, j'ai pas de blague\n");
	else if (type == B_ENV)
		ft_dprintf(fd_out, "je suis un env, PATH='PATH'\n");
	else
		ft_dprintf(fd_out, "Not supposed to happen in call print builtin\n");
}

/**
 * @brief Calls the three other built-ins, cd, unset and exit. Since they don't
 * print on STDOUT they don't need to be redirected.
 * 
 * @param branch The current CMD Branch.
 * @param type The built-in's index in the e_builtin enum.
 * @param cmd_number The current command number inside the pipeline.
 */
void	other_builtin(t_branch *branch, t_bltin type, int *cmd_number)
{
	if (type == B_CD)
		ft_printf("Je suis un cd, je change de directoire\n");
	else if (type == B_UNSET)
		ft_printf("Je suis un unset\n");
	else if (type == B_EXIT)
		ft_printf("Je suis un exit et j'exit (je crois)\n");
	else
		printf("Not supposed to happen in call non print builtin\n");
}

/**
 * @brief This function will execute the builtins when needed.
 * 
 * @param branch The current CMD Branch.
 * @param cmd_number The current command number inside the pipeline.
 * @return int Returns 0 on error and 1 on success.
 */
int	handle_builtins(t_branch *branch, int *cmd_number)
{
	t_bltin	type;
	int		infile;
	int		outfile;

	infile = UNDEFINED_FD;
	outfile = UNDEFINED_FD;
	type = is_built_in(branch);
	if (type == B_ERR)
		free_curr_branch(branch);
	open_redirections(&infile, &outfile, branch);
	if (infile >= 0)
		close(infile);
	if (infile == E_FD || outfile == E_FD)
	{
		if (outfile >= 0)
			close(outfile);
		return (0);
	}
	if (type <= B_ENV)
		printing_bltin(branch, type, outfile, cmd_number);
	close(outfile);
	if (type > B_ENV)
		other_builtin(branch, type, cmd_number);
}
