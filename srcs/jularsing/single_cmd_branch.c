/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:34 by jblaye            #+#    #+#             */
/*   Updated: 2024/03/26 15:35:59 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**generate_args_tab(t_pars_list **args)
{
	char		**args_tab;
	t_pars_list	*tmp;
	int			len;
	int			i;
	
	len = pars_list_size(*args);
	args_tab = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!args_tab)
		return (NULL);
	i = 0;
	tmp = *args;
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

t_cmd	*new_cmd(char **cmd_split, int hd_fd, char **env)
{
	t_cmd		*cmd;
	t_pars_list	**parsing;
	t_pars_list	*first_arg;
	t_pars_list	*first_file;
	
	parsing = extract_input_data(cmd_split);
	first_arg = parsing[0];
	first_file = parsing[1];
	if (!parsing)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd *));
	if (!cmd)
		return (NULL);
	cmd->args = generate_args_tab(&first_arg);
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->tree = generate_redir_tab(&first_file, hd_fd);
	if (!cmd->tree)
		return (free(cmd), ft_fsplit(cmd->args), NULL);
	cmd->cmd_path = fetch_cmd_path(cmd->args[0], env);
	return (cmd);
}
