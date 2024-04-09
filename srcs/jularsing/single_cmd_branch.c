/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:34 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/09 10:57:27 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_branch	**generate_redir_tab(t_pars_list *files, t_hd_fd_list *hd_fd_list)
{
	t_branch	**files_tab;
	t_pars_list	*tmp;
	int			len;
	int			i;

	len = pars_list_size(files);
	files_tab = (t_branch **) ft_calloc(len + 1, sizeof(t_branch *));
	if (!files_tab)
		return (NULL);
	i = 0;
	tmp = files;
	while (tmp)
	{
		files_tab[i] = generate_redir_branch(tmp, hd_fd_list);
		if (!files_tab)
			return (free_branch_tab(files_tab), NULL);
		tmp = tmp->next;
		i++;
	}
	pars_lst_clear(files);
	return (files_tab);
}

char	**generate_args_tab(t_pars_list *args)
{
	char		**args_tab;
	t_pars_list	*tmp;
	int			len;
	int			i;

	len = pars_list_size(args);
	args_tab = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!args_tab)
		return (NULL);
	i = 0;
	tmp = args;
	while (tmp)
	{
		args_tab[i] = ft_strdup(tmp->s);
		if (!args_tab[i])
			return (ft_fsplit(args_tab), NULL);
		tmp = tmp->next;
		i++;
	}
	pars_lst_clear(args);
	return (args_tab);
}

t_cmd	*new_cmd(char **cmd_split, t_hd_fd_list *hd_fd_list, char **env)
{
	t_cmd		*cmd;
	t_pars_list	*first_arg;
	t_pars_list	*first_file;

	cmd = NULL;
	first_arg = NULL;
	first_file = NULL;
	extract_input_data(cmd_split, &first_arg, &first_file);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = generate_args_tab(first_arg);
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->tree = generate_redir_tab(first_file, hd_fd_list);
	if (!cmd->tree)
		return (free(cmd), ft_fsplit(cmd->args), NULL);
	cmd->cmd_path = fetch_cmd_path(cmd->args[0], env);
	return (cmd);
}
