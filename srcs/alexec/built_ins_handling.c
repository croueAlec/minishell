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
int	is_built_in(t_branch *branch)
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
		if (ft_strncmp(cmd_name, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (i + 1);
		i++;
	}
	return (0);
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
int	printing_bltin(t_branch *br, t_bltin type, int fd_out, size_t *cmd_nbr)
{
	int	err_no;

	if (fd_out == UNDEFINED_FD)
		fd_out = STDOUT_FILENO;
	if (type == B_ECHO)
		err_no = echo_built_in(br, fd_out);
	else if (type == B_PWD)
		err_no = pwd_built_in(fd_out);
	else if (type == B_EXPORT)
		err_no = export_built_in(br, fd_out);
	else if (type == B_ENV)
		err_no = env_built_in(br->elmnt, fd_out);
	else
		err_no = 188;
	(void)br;
	(void)cmd_nbr;
	return (err_no);
}

/**
 * @brief Calls the three other built-ins, cd, unset and exit. Since they don't
 * print on STDOUT they don't need to be redirected.
 * 
 * @param branch The current CMD Branch.
 * @param type The built-in's index in the e_builtin enum.
 * @param cmd_number The current command number inside the pipeline.
 */
int	other_builtin(t_branch *branch, t_bltin type, size_t *cmd_number)
{
	int	err_no;

	err_no = 0;
	if (type == B_CD)
		err_no = cd_built_in(branch->elmnt);
	else if (type == B_UNSET)
		err_no = unset_built_in(branch);
	else if (type == B_EXIT)
		err_no = exit_built_in(branch, cmd_number);
	else
		err_no = printf("Not supposed to happen in call non print builtin\n");
	(void)branch;
	(void)cmd_number;
	return (err_no);
}

/**
 * @brief This function will execute the builtins when needed.
 * 
 * @param branch The current CMD Branch.
 * @param cmd_number The current command number inside the pipeline.
 * @return int Returns 0 on error and 1 on success.
 */
int	handle_builtins(t_branch *branch, size_t *cmd_number, int outfile)
{
	t_bltin	type;
	int		infile;
	int		err_no;

	err_no = 0;
	infile = UNDEFINED_FD;
	type = is_built_in(branch);
	if (type == B_ERR)
		free_curr_branch(branch);
	open_redirections(&infile, &outfile, branch);
	if (infile >= 0)
		close(infile);
	if (infile == E_FD || outfile == E_FD)
	{
		if (outfile >= 0 && !isatty(outfile))
			close(outfile);
		return (1);
	}
	if (type <= B_ENV)
		err_no = printing_bltin(branch, type, outfile, cmd_number);
	if (!isatty(outfile) && outfile >= 0)
		close(outfile);
	if (type > B_ENV)
		err_no = other_builtin(branch, type, cmd_number);
	return (err_no);
}
